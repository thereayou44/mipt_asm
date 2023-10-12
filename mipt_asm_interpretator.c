#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <string>
#include <cctype>
#include <fstream>


using namespace std;
int cnt = 0 ;
enum type {
    RM = 0,
    RR = 1,
    RI = 2,
    J = 3
};

enum code {
    HALT = 0,
    SYSCALL = 1,
    ADD = 2,
    ADDI = 3,
    SUB = 4,
    SUBI = 5,
    MUL = 6,
    MULI = 7,
    DIV = 8,
    DIVI = 9,
    LC = 12,
    SHL = 13,
    SHLI = 14,
    SHR = 15,
    SHRI = 16,
    AND = 17,
    ANDI = 18,
    OR = 19,
    ORI = 20,
    XOR = 21,
    XORI = 22,
    NOT = 23,
    MOV = 24,
    ADDD = 32,
    SUBD = 33,
    MULD = 34,
    DIVD = 35,
    ITOD = 36,
    DTOI = 37,
    PUSH = 38,
    POP = 39,
    CALL = 40,
    CALLI = 41,
    RET = 42,
    CMP = 43,
    CMPI = 44,
    CMPD = 45,
    JMP = 46,
    JNE = 47,
    JEQ = 48,
    JLE = 49,
    JL = 50,
    JGE = 51,
    JG = 52,
    LOAD = 64,
    STORE = 65,
    LOAD2 = 66,
    STORE2 = 67,
    LOADR = 68,
    LOADR2 = 69,
    STORER = 70,
    STORER2 = 71,
    SKIP = -1
};
map<string, code> map_of_codes = {{"halt", HALT}, {"syscall", SYSCALL}, {"add", ADD}, {"addi", ADDI},
                                  {"sub", SUB}, {"subi", SUBI}, {"mul", MUL}, {"muli", MULI},
                                  {"div", DIV}, {"divi", DIVI}, {"lc", LC}, {"shl", SHL},
                                  {"shli", SHLI}, {"shr", SHR}, {"shri", SHRI}, {"and", AND},
                                  {"andi", ANDI}, {"or", OR}, {"ori", ORI}, {"xor", XOR},
                                  {"xori", XORI}, {"not", NOT}, {"mov", MOV}, {"addd", ADDD},
                                  {"subd", SUBD}, {"muld", MULD}, {"divd", DIVD}, {"itod", ITOD},
                                  {"dtoi", DTOI}, {"push", PUSH}, {"pop", POP}, {"call", CALL},
                                  {"calli", CALLI}, {"ret", RET}, {"cmp", CMP}, {"cmpi", CMPI},
                                  {"cmpd", CMPD}, {"jmp", JMP}, {"jne", JNE}, {"jeq", JEQ},
                                  {"jle", JLE}, {"jl", JL}, {"jge", JGE}, {"jg", JG},
                                  {"load", LOAD}, {"store", STORE}, {"load2", LOAD2}, {"store2", STORE2},
                                  {"loadr", LOADR}, {"loadr2", LOADR2}, {"storer", STORER}, {"storer2", STORER2}};
static stack<int> st;
union ll {
    long long w;
    struct { int x, y; };
};
int q = 0 ;
struct command {
    int code;
    int type;

    void (*func)(int a, int b, int c);
};
void skip (int a, int b, int c) {

}


map <int, string> code{
        {0, "halt"},
        {1, "syscall"},
        {2, "add"},
        {3, "addi"},
        {4, "sub"},
        {5, "subi"},
        {6, "mul"},
        {7, "muli"},
        {8, "div"},
        {9, "divi"},
        {12, "lc"},
        {13, "shl"},
        {14, "shli"},
        {15, "shr"},
        {16, "shri"},
        {17, "and_"},
        {18, "and_i"},
        {19, "or_"},
        {20, "or_i"},
        {21, "xorr"},
        {22, "xori"},
        {23, "ne"},
        {24, "mov"},
        {32, "addd"},
        {33, "subd"},
        {34, "muld"},
        {35, "divd"},
        {36, "itod"},
        {37, "dtoi"},
        {38, "push"},
        {39, "pop"},
        {40, "call"},
        {41, "calli"},
        {42, "ret"},
        {43, "cmp"},
        {44, "cmpi"},
        {45, "cmpd"},
        {46, "jmp"},
        {47, "jne"},
        {48, "jeq"},
        {49, "jle"},
        {50, "jl"},
        {51, "jge"},
        {52, "jg"},
        {64, "load"},
        {65, "store"},
        {66, "load2"},
        {67, "store2"},
        {68, "loadr"},
        {69, "loadr2"},
        {70, "storer"},
        {71, "storer2"},
        {-1, "skip" }
};
map <int,int> reg = {
        {0, 0},
        {1, 0},
        {2, 0},
        {3, 0},
        {4, 0},
        {5, 0},
        {6, 0},
        {7, 0},
        {8, 0},
        {9, 0},
        {10, 0},
        {11, 0},
        {12, 0},
        {13, 0},
        {14, 1048575},
        {15, 0}
};
map <string, int> flag={
        {"EF" , 0},
        {"CMP", 0}
};
int mem[1<<20];
void halt(int rg, int q1, int q2)
{
    flag["EF"] = 1;
}
void syscall(int rg, int a, int q)
{
   // cout << a   << " | " << reg[rg] << endl;
    switch (a) {
        case 0:
            flag["EF"] = 1;
            break;
        case 100: {
            int n; scanf("%d", &n);
            reg[rg] = n;
            break;
        }
        case 101: {
            double x; cin >> x;
            int arr[2] = {0, 0};
            memcpy(arr, &x, sizeof(double));
            reg[rg] = arr[0];
            reg[rg + 1] = arr[1];
            break;
        }
        case 102:
            cout << reg[rg];
            break;
        case 103: {
            double d; int arr[2] = {reg[rg], reg[rg + 1]};
            memcpy(&d, arr, sizeof(double));
            printf("%lg", d);
            break;
        }
        case 104: {
            char c; cin >> c;
            reg[rg] = c;
            break;
        }
        case 105:
            cout << char(reg[rg]);
            break;
    }
}
void add(int r_des, int r, int n)
{
    reg[r_des] += (reg[r] + n);
}
void addi(int r, int a, int q)
{
    if (r == 6)
        cnt ++ ;
    reg[r] += a;
}
void sub(int r_des, int r, int n)
{
    reg[r_des] -= (reg[r] + n);
}
void subi(int r, int n, int q)
{
    reg[r] -= n;
}

void mul(int r_des, int r, int n)
{
    long long storage = (long long)((long long)(reg[r_des]) * (long long)(reg[r] + n)) ;
    ll ans{storage};
    reg[r_des] = ans.x;
    reg[r_des+1] = ans.y;
}
void muli(int r_des, int n, int q)
{
    long long storage = (long long)((long long)(reg[r_des]) * (long long)(n)) ;
    ll ans{storage};
    reg[r_des] = ans.x;
    reg[r_des+1] = ans.y;
}
void div(int r_des, int r, int n)
{
    ll a{};
    a.x = reg[r_des];
    a.y = reg[r_des + 1];
    reg[r_des] =static_cast<int32_t>(a.w / (reg[r] + n));
    reg[r_des + 1] = static_cast<int32_t>(a.w % (reg[r] + n));
}
void divi(int r_des, int n, int q)
{
    ll a{};
    a.x = reg[r_des];
    a.y = reg[r_des + 1];
    reg[r_des] =static_cast<int32_t>(a.w / (n));
    reg[r_des + 1] = static_cast<int32_t>(a.w % (n));
}
void lc(int r_des, int n, int q)
{
    reg[r_des] = n;
}
void shl(int r_des, int r, int n)
{
     reg[r_des] = reg[r_des] << (reg[r] + n);
}
void shli(int r_des, int n, int q)
{
    reg[r_des] = (reg[r_des] << n);
}
void shr(int r_des, int r, int n)
{
    reg[r_des] = reg[r_des] >> (reg[r] + n);
}
void shri(int r_des, int n, int q)
{
    reg[r_des] = (reg[r_des] >> n);
}
void and_(int r_des, int r, int n)
{
    reg[r_des] = reg[r_des] & (reg[r]+n);
}
void and_i(int r_des, int n, int q)
{
    reg[r_des] = reg[r_des] & n;
}
void or_(int r_des, int r, int n)
{
    reg[r_des] = reg[r_des] | (reg[r] + n);
}
void or_i(int r_des, int n, int q)
{
    reg[r_des] = reg[r_des] | n;
}
void xorr(int r_des, int r, int n)
{
    reg[r_des] = reg[r_des] ^ (reg[r] + n);
}
void xorri(int r_des, int n, int q)
{
    reg[r_des] = reg[r_des] ^ n ;
}
void ne(int r_des, int n, int q)
{
    reg[r_des] = ~(reg[r_des]);
}
void mov(int r_des, int r ,int n)
{
    reg[r_des] = static_cast<int32_t>(reg[r] + n);
}
void addd(int r_des, int r, int n)
{
    double d1, d2;
    int arr1[2] = {reg[r_des], reg[r_des + 1]},
        arr2[2] = {reg[r], reg[r + 1]};
    memcpy(&d1, arr1, sizeof(double));
    memcpy(&d2, arr2, sizeof(double));
    d1 += d2;
    memcpy(arr1, &d1, sizeof(double));
    reg[r_des] = arr1[0]; reg[r_des + 1] = arr1[1];
}
void subd(int r_des, int r, int n)
{
    double d1, d2;
    int arr1[2] = {reg[r_des], reg[r_des + 1]},
            arr2[2] = {reg[r], reg[r + 1]};
    memcpy(&d1, arr1, sizeof(double));
    memcpy(&d2, arr2, sizeof(double));
    d1 -= d2;
    memcpy(arr1, &d1, sizeof(double));
    reg[r_des] = arr1[0]; reg[r_des + 1] = arr1[1];
}
void muld(int r_des, int r, int n)
{
    double d1, d2;
    int arr1[2] = {reg[r_des], reg[r_des + 1]},
            arr2[2] = {reg[r], reg[r + 1]};
    memcpy(&d1, arr1, sizeof(double));
    memcpy(&d2, arr2, sizeof(double));
    d1 *= d2;
    memcpy(arr1, &d1, sizeof(double));
    reg[r_des] = arr1[0]; reg[r_des + 1] = arr1[1];
}
void divd(int r_des, int r, int n)
{
    double d1, d2;
    int arr1[2] = {reg[r_des], reg[r_des + 1]},
            arr2[2] = {reg[r], reg[r + 1]};
    memcpy(&d1, arr1, sizeof(double));
    memcpy(&d2, arr2, sizeof(double));
    d1 /= d2;
    memcpy(arr1, &d1, sizeof(double));
    reg[r_des] = arr1[0]; reg[r_des + 1] = arr1[1];
}
void itod(int r_des, int r, int n)
{
    double d1 = (double)(reg[r]);
    int arrd[2] ;
    memcpy(arrd, &d1, sizeof(double));
    reg[r_des] = arrd[0]; reg[r_des + 1] = arrd[1];
}
void dtoi(int r_des, int r, int n)
{
    double d;
    int arr[2] = {reg[r], reg[r + 1]};
    memcpy(&d, arr, sizeof(double));
    int a = (int)(d);
    int arri[2];
    memcpy(arri, &a, sizeof(double));
    reg[r_des] = arri[0]; reg[r_des + 1] = arri[1];
}
void push(int r_des, int n, int q)
{
    mem[reg[14]--] = reg[r_des] + n;
}
void pop(int r_des, int n, int q)
{
    reg[r_des] = (mem[++reg[14]] + n);
}
void call(int idx1, int idx2, int q)
{
    st.push(reg[15]);
    reg[15] = reg[idx2] + 127 + mem[5];
    reg[idx1] = reg[15];
}
void calli(int idx, int q1, int q2)
{
    st.push(reg[15]);
    reg[15] = idx + 127 + mem[5];
}
void ret(int idx, int q1,int q2)
{
    reg[14] += q1;
    reg[15] = st.top();
    st.pop();
}

void cmp(int r1, int r2, int n)
{
    if (reg[r1] > reg[r2])
        flag["CMP"] = 1 ;
    else
        if (reg[r1] < reg[r2])
            flag["CMP"] = -1;
        else
            if (reg[r1] == reg[r2])
                flag["CMP"] = 0 ;
}
void cmpi(int r, int c, int q)
{
    cnt ++ ;
    if (reg[r] > c)
        flag["CMP"] = 1 ;
    else
    if (reg[r] < c)
        flag["CMP"] = -1;
    else
    if (reg[r] == c)
        flag["CMP"] = 0 ;
}
void cmpd(int r1, int r2, int n)
{
    if (reg[r1] > reg[r2])
        flag["CMP"] = 1 ;
    else
        if (reg[r1] < reg[r2])
            flag["CMP"] = -1;
        else
        if (reg[r1 + 1] < reg[r2 + 1])
            flag["CMP"] = -1;
        else
        if (reg[r1 + 1] > reg[r2 + 1])
            flag["CMP"] = 1;
        else
            flag["CMP"] = 0;
}
void jmp(int idx, int q1, int q2)
{
    reg[15] = idx + 127 + mem[5];
}
void jne(int idx, int q1, int q2)
{
    if (flag["CMP"])
        reg[15] = idx + 127 + mem[5];
}
void jeq(int idx, int q1, int q2)
{
    if (!flag["CMP"])
        reg[15] = + 127 + mem[5];
}
void jle(int idx, int q1, int q2)
{
    if (flag["CMP"] != 1)
        reg[15] = idx + 127 + mem[5];
}
void jl(int idx, int q1, int q2)
{
    if (flag["CMP"] == -1)
        reg[15] = idx + 127 + mem[5];
}
void jge(int idx, int q1, int q2)
{
    if (flag["CMP"] != -1)
        reg[15] =idx + 127 + mem[5];
}
void jg(int idx,int q1, int q2)
{
    if (flag["CMP"] == 1)
        reg[15] = idx + 127 + mem[5];
}
void load(int r_des, int me, int q)
{
    reg[r_des] = mem[me];
}
void store(int r0, int me, int q)
{
    mem[me] = reg[r0];
}
void load2(int r_des, int me, int q)
{
    reg[r_des] = mem[me];
       reg[r_des + 1] = mem[me + 1];
}
void store2(int r0, int me, int q)
{
    mem[me] = reg[r0];
    mem[me + 1] = reg[r0 + 1];
}
void loadr(int r_des, int r, int n)
{
    reg[r_des] = mem[reg[r] + n];
}
void loadr2(int r_des, int r, int n)
{
    reg[r_des] = mem[reg[r] + n];
    reg[r_des + 1] = mem[reg[r] + n + 1];
}
void storer(int r, int r_des, int n)
{
    mem[r_des + n] = reg[r];
}
void storer2(int r, int r_des, int n)
{
    mem[reg[r_des] + n] = reg[r];
    mem[reg[r_des] + n + 1] = reg[r + 1];
}
vector<command> funcs{
        {0, RI, halt}, {1, RI, syscall}, {2, RR, add},
        {3, RI, addi}, {4, RR, sub}, {5, RI, subi},
        {6, RR, mul}, {7, RI, muli}, {8, RR, div},
        {9, RI, divi}, {10, J, skip}, {11, J, skip},
        {12, RI, lc}, {13, RR, shl}, {14, RI, shli},
        {15, RR, shr}, {16, RI, shri}, {17, RR, and_},
        {18, RI, and_i}, {19, RR, or_}, {20, RI, or_i},
        {21, RR, xorr}, {22, RI, xorri}, {23, RI, ne},
        {24, RR, mov}, {25, J, skip}, {26, J, skip},
        {27, J, skip}, {28, J, skip}, {29, J, skip},
        {30, J, skip}, {31, J, skip}, {32, RR, addd},
        {33, RR, subd}, {34, RR, muld}, {35, RR, divd},
        {36, RR, itod}, {37, RR, dtoi}, {38, RI, push},
        {39, RI, pop}, {40, RR, call}, {41, J, calli},
        {42, RI, ret}, {43, RR, cmp}, {44, RI, cmpi},
        {45, RR, cmpd}, {46, J, jmp}, {47, J, jne},
        {48, J, jeq}, {49, J, jle}, {50, J, jl},
        {51, J, jge}, {52, J, jg}, {53, J, skip},
        {54, J, skip}, {55, J, skip}, {56, J, skip},
        {57, J, skip}, {58, J, skip}, {59, J, skip},
        {60, J, skip}, {61, J, skip}, {62, J, skip},
        {63, J, skip}, {64, RM, load}, {65, RM, store},
        {66, RM, load2}, {67, RM, store2}, {68, RR, loadr},
        {69, RR, storer}, {70, RR, loadr2}, {71, RR, storer2}
};

static map<string, int> mark;

string ar[200];
bool ud[200];
char buf[20000];
int main() {
    FILE *fp = fopen("input.bin", "rb");
    fseek(fp, 0 , SEEK_END);
    int count_of_elems = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    fread(buf, sizeof(char), count_of_elems, fp);
    memcpy(mem, buf, count_of_elems);
    int start_pos = mem[7];
    int size = mem[4];
    for (reg[15] = (128 + start_pos); reg[15] < 128 + size + mem[5]; reg[15] ++)
    {
            int cmd = (mem[reg[15]] >> 24) ;
   switch(funcs[cmd].type)
        {
            case RR: {
                int r1 = (mem[reg[15]] >> 20) & 0xf;
                int r2 = (mem[reg[15]] >> 16) & 0xf;
                int n = (mem[reg[15]] & 0xffff);
                funcs[cmd].func(r1, r2, n);
                break;
            }
            case RI:
            case RM: {
                int r1 = (mem[reg[15]] >> 20) & 0xf;
                int n = (mem[reg[15]] & 0xfffff);
                funcs[cmd].func(r1, n, 0);
                break;
            }
            case J: {
                int n = (mem[reg[15]] & 0xfffff);
                funcs[cmd].func(n,0,0);
                break;
            }
            default:
                break;
        }
        if (flag["EF"] == 1)
            break ;
    }
}
