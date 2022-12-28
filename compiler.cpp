#include <fstream>
#include <string>
#include <iostream>
using namespace std;
// prototypes
void dasturat(string tokenList[][3]);
void amaliat(string tokenList[][3]);
void functionParameter(string tokenList[][3]);

// global variables
bool lexicalError = false;
int tokenCount = 0;
string lookahead;
int tokenIndex = 0;

// syntatic phase
void syntaticErrorManager(string tokenList[][3])
{
    cout << "Fix the Syntatic error that is included below and run the program again" << endl
         << tokenList[tokenIndex - 1][1] << ":" << tokenList[tokenIndex - 1][2] << " --> ";
    for (int i = 2; i < tokenList[tokenIndex - 1][0].length(); i++)
        cout << tokenList[tokenIndex - 1][0][i];
    exit(0);
}
void match(string input, string tokenList[][3])
{
    if (lookahead == input)
    {
        if (tokenIndex < tokenCount)
            lookahead = tokenList[tokenIndex++][0];
        else
            lookahead = "";
    }
    else
        syntaticErrorManager(tokenList);
}

void meqdar(string tokenList[][3])
{
    if (lookahead == "t_@")
        match("t_@", tokenList);
    else if (lookahead == "t_-")
    {
        match("t_-", tokenList);
        match("t_@", tokenList);
    }
    else
        syntaticErrorManager(tokenList);
}
void meqdardehi(string tokenList[][3])
{
    if (lookahead == "t_shenase")
    {
        match("t_shenase", tokenList);
        match("t_eq", tokenList);
        amaliat(tokenList);
    }
    else
        syntaticErrorManager(tokenList);
}
void amalgarHesabi(string tokenList[][3])
{
    if (lookahead == "t_pl")
        match("t_pl", tokenList);
    else if (lookahead == "t_mi")
        match("t_mi", tokenList);
    else if (lookahead == "t_mu")
        match("t_mu", tokenList);
    else if (lookahead == "t_di")
        match("t_di", tokenList);
    else
        syntaticErrorManager(tokenList);
}
void FIX_amaliat(string tokenList[][3])
{
    if (lookahead == "t_pl" || lookahead == "t_mi" || lookahead == "t_mu" || lookahead == "t_di")
    {
        amalgarHesabi(tokenList);
        amaliat(tokenList);
        FIX_amaliat(tokenList);
    }
    else
        return;
}
void amaliat(string tokenList[][3])
{
    if (lookahead == "t_@")
    {
        match("t_@", tokenList);
        FIX_amaliat(tokenList);
    }
    else
        syntaticErrorManager(tokenList);
}
void amalgarSharti(string tokenList[][3])
{
    if (lookahead == "t_?>")
        match("t_?>", tokenList);
    else if (lookahead == "t_?<")
        match("t_?<", tokenList);
    else if (lookahead == "t_?=")
        match("t_?=", tokenList);
    else
        syntaticErrorManager(tokenList);
}
void shart(string tokenList[][3])
{
    if (lookahead == "t_-" || lookahead == "t_@")
    {
        amaliat(tokenList);
        amalgarSharti(tokenList);
        amaliat(tokenList);
    }
    else if (lookahead == "t_yox")
        match("t_yox", tokenList);
    else if (lookahead == "t_han")
        match("t_han", tokenList);
    else
        syntaticErrorManager(tokenList);
}
void functionCall(string tokenList[][3])
{
    if (lookahead == "t_run")
    {
        match("t_run", tokenList);
        match("t_shenase", tokenList);
        match("t_/", tokenList);
        functionParameter(tokenList);
        match("t_\\", tokenList);
    }
    else
        syntaticErrorManager(tokenList);
}
void functionReturn(string tokenList[][3])
{
    if (lookahead == "t_give")
    {
        match("t_give", tokenList);
        meqdar(tokenList);
    }
    else
        return;
}
void FIX_functionParameter(string tokenList[][3])
{
    match("t_shenase", tokenList);
    if (lookahead == "t_eq")
    {
        match("t_eq", tokenList);
        amaliat(tokenList);
    }

    if (lookahead == "t_dishdadadadam")
    {
        match("t_dishdadadadam", tokenList);
        functionParameter(tokenList);
    }
    else
        return;
}
void functionParameter(string tokenList[][3])
{
    if (lookahead == "t_shenase" || lookahead == "t_eq")
        FIX_functionParameter(tokenList);
    else
        return;
}
void functionDefine(string tokenList[][3])
{
    if (lookahead == "t_remember")
    {
        match("t_remember", tokenList);
        match("t_shenase", tokenList);
        match("t_/", tokenList);
        functionParameter(tokenList);
        match("t_\\", tokenList);
        dasturat(tokenList);
        functionReturn(tokenList);
        dasturat(tokenList);
        match("t_/", tokenList);
    }
    else
        syntaticErrorManager(tokenList);
}
void halqe(string tokenList[][3])
{
    if (lookahead == "t_tandis")
    {
        match("t_tandis", tokenList);
        match("t_/", tokenList);
        shart(tokenList);
        match("t_\\", tokenList);
        dasturat(tokenList);
        match("t_/", tokenList);
    }
    else if (lookahead == "t_pour")
    {
        match("t_pour", tokenList);
        match("t_/", tokenList);
        meqdardehi(tokenList);
        match("t_dishdadadadam", tokenList);
        shart(tokenList);
        match("t_dishdadadadam", tokenList);
        meqdardehi(tokenList);
        match("t_\\", tokenList);
        dasturat(tokenList);
        match("t_/", tokenList);
    }
    else
        return;
}
void dasturSharti3(string tokenList[][3])
{
    if (lookahead == "t_autre")
    {
        match("t_autre", tokenList);
        match("t_\\", tokenList);
        dasturat(tokenList);
        match("t_/", tokenList);
    }
    else
        return;
}
void dasturSharti2(string tokenList[][3])
{
    if (lookahead == "t_autresi")
    {
        match("t_autresi", tokenList);
        match("t_/", tokenList);
        shart(tokenList);
        match("t_\\", tokenList);
        dasturat(tokenList);
        match("t_/", tokenList);
        dasturSharti2(tokenList);
        dasturSharti3(tokenList);
    }
    else
        return;
}
void dasturSharti(string tokenList[][3])
{
    if (lookahead == "t_si")
    {
        match("t_si", tokenList);
        match("t_/", tokenList);
        shart(tokenList);
        match("t_\\", tokenList);
        dasturat(tokenList);
        match("t_/", tokenList);
        dasturSharti2(tokenList);
        dasturSharti3(tokenList);
    }
    else
        syntaticErrorManager(tokenList);
}
void FIX_shart_amaliat_meqdar(string tokenList[][3])
{
    meqdar(tokenList);
    if (lookahead == "t_pl" || lookahead == "t_mi" || lookahead == "t_mu" || lookahead == "t_di")
    {
        amalgarHesabi(tokenList);
        amaliat(tokenList);
        FIX_amaliat(tokenList);
        if (lookahead == "t_?=" || lookahead == "t_?>" || lookahead == "t_?<")
        {
            amalgarSharti(tokenList);
            amaliat(tokenList);
        }
    }
    else
        return;
}
void FIX_meqdardehi_shenase(string tokenList[][3])
{
    match("t_shenase", tokenList);
    if (lookahead == "t_eq")
    {
        match("t_eq", tokenList);
        amaliat(tokenList);
    }
    else
        return;
}
void dasturat(string tokenList[][3])
{
    // shart
    if (lookahead == "t_si")
    {
        dasturSharti(tokenList);
        dasturat(tokenList);
    }
    // halqe
    else if (lookahead == "t_tandis" || lookahead == "t_pour")
    {
        halqe(tokenList);
        dasturat(tokenList);
    }
    // taarif tabe
    else if (lookahead == "t_remember")
    {
        functionDefine(tokenList);
        dasturat(tokenList);
    }
    // faraxani tabe
    else if (lookahead == "t_run")
    {
        functionCall(tokenList);
        dasturat(tokenList);
    }
    // shart
    else if (lookahead == "t_han" || lookahead == "t_yox")
    {
        shart(tokenList);
        dasturat(tokenList);
    }
    // meqdardehi -- shenase
    else if (lookahead == "t_shenase")
    {
        FIX_meqdardehi_shenase(tokenList);
        dasturat(tokenList);
    }
    // meqdar -- amaliat --  shart
    else if (lookahead == "t_-" || lookahead == "t_@")
    {
        FIX_shart_amaliat_meqdar(tokenList);
        dasturat(tokenList);
    }
    else
        return;
}

// lexical phase
string checkKeyWord(string lexeme) // si autre autresi tandis pour remember run give han yox
{
    int state = 1;
    char ch;
    bool lastChar = false;
    string output;

    for (int i = 0; i <= lexeme.length() + 1; i++)
    {
        if (i == lexeme.length())
            lastChar = true;
        ch = lexeme[i];

        switch (state)
        {
        case 0: // trap
            return "error";
            break;
        case 1:
            if (ch == 's')
                state = 2;
            else if (ch == 'a')
                state = 4;
            else if (ch == 't')
                state = 11;
            else if (ch == 'p')
                state = 17;
            else if (ch == 'r')
                state = 21;
            else if (ch == 'g')
                state = 31;
            else if (ch == 'h')
                state = 35;
            else if (ch == 'y')
                state = 38;
            else
                state = 0;
            break;
        case 2:
            if (ch == 'i')
                state = 3;
            else
                state = 0;
            break;
        case 3:
            if (lastChar)
            {
                lastChar = false;
                return "t_si";
            }
            else
                state = 0;
            break;
        case 4:
            if (ch == 'u')
                state = 5;
            else
                state = 0;
            break;
        case 5:
            if (ch == 't')
                state = 6;
            else
                state = 0;
            break;
        case 6:
            if (ch == 'r')
                state = 7;
            else
                state = 0;
            break;
        case 7:
            if (ch == 'e')
                state = 8;
            else
                state = 0;
            break;
        case 8:
            if (lastChar)
            {
                lastChar = false;
                return "t_autre";
            }
            else if (ch == 's')
                state = 9;
            else
                state = 0;
            break;
        case 9:
            if (ch == 'i')
                state = 10;
            else
                state = 0;
            break;
        case 10:
            if (lastChar)
            {
                lastChar = false;
                return "t_autresi";
            }
            else
                state = 0;
            break;
        case 11:
            if (ch == 'a')
                state = 12;
            else
                state = 0;
            break;
        case 12:
            if (ch == 'n')
                state = 13;
            else
                state = 0;
            break;
        case 13:
            if (ch == 'd')
                state = 14;
            else
                state = 0;
            break;
        case 14:
            if (ch == 'i')
                state = 15;
            else
                state = 0;
            break;
        case 15:
            if (ch == 's')
                state = 16;
            else
                state = 0;
            break;
        case 16:
            if (lastChar)
            {
                lastChar = false;
                return "t_tandis";
            }
            else
                state = 0;
            break;
        case 17:
            if (ch == 'o')
                state = 18;
            else
                state = 0;
            break;
        case 18:
            if (ch == 'u')
                state = 19;
            else
                state = 0;
            break;
        case 19:
            if (ch == 'r')
                state = 20;
            else
                state = 0;
            break;
        case 20:
            if (lastChar)
            {
                lastChar = false;
                return "t_pour";
            }
            else
                state = 0;
            break;
        case 21:
            if (ch == 'e')
                state = 22;
            else if (ch == 'u')
                state = 29;
            else
                state = 0;
            break;
        case 22:
            if (ch == 'm')
                state = 23;
            else
                state = 0;
            break;
        case 23:
            if (ch == 'e')
                state = 24;
            else
                state = 0;
            break;
        case 24:
            if (ch == 'm')
                state = 25;
            else
                state = 0;
            break;
        case 25:
            if (ch == 'b')
                state = 26;
            else
                state = 0;
            break;
        case 26:
            if (ch == 'e')
                state = 27;
            else
                state = 0;
            break;
        case 27:
            if (ch == 'r')
                state = 28;
            else
                state = 0;
            break;
        case 28:
            if (lastChar)
            {
                lastChar = false;
                return "t_remember";
            }
            else
                state = 0;
            break;
        case 29:
            if (ch == 'n')
                state = 30;
            else
                state = 0;
            break;
        case 30:
            if (lastChar)
            {
                lastChar = false;
                return "t_run";
            }
            else
                state = 0;
            break;
        case 31:
            if (ch == 'i')
                state = 32;
            else
                state = 0;
            break;
        case 32:
            if (ch == 'v')
                state = 33;
            else
                state = 0;
            break;
        case 33:
            if (ch == 'e')
                state = 34;
            else
                state = 0;
            break;
        case 34:
            if (lastChar)
            {
                lastChar = false;
                return "t_give";
            }
            else
                state = 0;
            break;
        case 35:
            if (ch == 'a')
                state = 36;
            else
                state = 0;
            break;
        case 36:
            if (ch == 'n')
                state = 37;
            else
                state = 0;
            break;
        case 37:
            if (lastChar)
            {
                lastChar = false;
                return "t_han";
            }
            else
                state = 0;
            break;
        case 38:
            if (ch == 'o')
                state = 39;
            else
                state = 0;
            break;
        case 39:
            if (ch == 'x')
                state = 40;
            else
                state = 0;
            break;
        case 40:
            if (lastChar)
            {
                lastChar = false;
                return "t_yox";
            }
            else
                state = 0;
            break;
        }
    }

    return "";
}
string checkShenase(string lexeme)
{
    int state = 1;
    char ch;
    bool lastChar = false;
    string output;

    for (int i = 0; i <= lexeme.length() + 1; i++)
    {
        if (i == lexeme.length())
            lastChar = true;
        ch = lexeme[i];

        switch (state)
        {
        case 0: // trap
            return "error";
            break;
        case 1:
            if (ch == 'i')
                state = 2;
            else
                state = 0;
            break;
        case 2:
            if (ch == '_')
                state = 3;
            else
                state = 0;
            break;
        case 3:
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch >= '0' && ch <= '9')
                state = 4;
            else
                state = 0;
            break;
        case 4:
            if (lastChar)
            {
                lastChar = false;
                return "t_shenase";
            }
            else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch >= '0' && ch <= '9')
                state = 4;
            else
                state = 0;
            break;
        }
    }

    return "";
}
string checkSplitter(string lexeme) // dishdadadadam
{
    int state = 1;
    char ch;
    bool lastChar = false;
    string output;

    for (int i = 0; i <= lexeme.length() + 1; i++)
    {
        if (i == lexeme.length())
            lastChar = true;
        ch = lexeme[i];

        switch (state)
        {
        case 0: // trap
            return "error";
            break;
        case 1:
            if (ch == 'd')
                state = 2;
            else
                state = 0;
            break;
        case 2:
            if (ch == 'i')
                state = 3;
            else
                state = 0;
            break;
        case 3:
            if (ch == 's')
                state = 4;
            else
                state = 0;
            break;
        case 4:
            if (ch == 'h')
                state = 5;
            else
                state = 0;
            break;
        case 5:
            if (ch == 'd')
                state = 6;
            else
                state = 0;
            break;
        case 6:
            if (ch == 'a')
                state = 7;
            else
                state = 0;
            break;
        case 7:
            if (ch == 'd')
                state = 8;
            else
                state = 0;
            break;
        case 8:
            if (ch == 'a')
                state = 9;
            else
                state = 0;
            break;
        case 9:
            if (ch == 'd')
                state = 10;
            else
                state = 0;
            break;
        case 10:
            if (ch == 'a')
                state = 11;
            else
                state = 0;
            break;
        case 11:
            if (ch == 'd')
                state = 12;
            else
                state = 0;
            break;
        case 12:
            if (ch == 'a')
                state = 13;
            else
                state = 0;
            break;
        case 13:
            if (ch == 'm')
                state = 14;
            else
                state = 0;
            break;
        case 14:
            if (lastChar)
            {
                lastChar = false;
                return "t_dishdadadadam";
            }
            else
                state = 0;
            break;
        }
    }

    return "";
}
string checkOperand(string lexeme) // ?=   ?>   ?<   eq   pl   mi   mu   di   -  \  /
{
    int state = 1;
    char ch;
    bool lastChar = false;
    string output;

    for (int i = 0; i <= lexeme.length() + 1; i++)
    {
        if (i == lexeme.length())
            lastChar = true;
        ch = lexeme[i];

        switch (state)
        {
        case 0: // trap
            return "error";
            break;
        case 1:
            if (ch == '?')
                state = 2;
            else if (ch == 'e')
                state = 6;
            else if (ch == 'p')
                state = 8;
            else if (ch == 'm')
                state = 10;
            else if (ch == 'd')
                state = 13;
            else if (ch == '-')
                state = 15;
            else if (ch == '/')
                state = 16;
            else if (ch == '\\')
                state = 17;
            else
                state = 0;
            break;
        case 2:
            if (ch == '>')
                state = 3;
            else if (ch == '<')
                state = 4;
            else if (ch == '=')
                state = 5;
            else
                state = 0;
            break;
        case 3:
            if (lastChar)
            {
                lastChar = false;
                return "t_?>";
            }
            else
                state = 0;
            break;
        case 4:
            if (lastChar)
            {
                lastChar = false;
                return "t_?<";
            }
            else
                state = 0;
            break;
        case 5:
            if (lastChar)
            {
                lastChar = false;
                return "t_?=";
            }
            else
                state = 0;
            break;
        case 6:
            if (ch == 'q')
                state = 7;
            else
                state = 0;
            break;
        case 7:
            if (lastChar)
            {
                lastChar = false;
                return "t_eq";
            }
            else
                state = 0;
            break;
        case 8:
            if (ch == 'l')
                state = 9;
            else
                state = 0;
            break;
        case 9:
            if (lastChar)
            {
                lastChar = false;
                return "t_pl";
            }
            else
                state = 0;
            break;
        case 10:
            if (ch == 'i')
                state = 11;
            else if (ch == 'u')
                state = 12;
            else
                state = 0;
            break;
        case 11:
            if (lastChar)
            {
                lastChar = false;
                return "t_mi";
            }
            else
                state = 0;
            break;
        case 12:
            if (lastChar)
            {
                lastChar = false;
                return "t_mu";
            }
            else
                state = 0;
            break;
        case 13:
            if (ch == 'i')
                state = 14;
            else
                state = 0;
            break;
        case 14:
            if (lastChar)
            {
                lastChar = false;
                return "t_di";
            }
            else
                state = 0;
        case 15:
            if (lastChar)
            {
                lastChar = false;
                return "t_-";
            }
            else
                state = 0;
        case 16:
            if (lastChar)
            {
                lastChar = false;
                return "t_/";
            }
            else
                state = 0;
        case 17:
            if (lastChar)
            {
                lastChar = false;
                return "t_\\";
            }
            else
                state = 0;
        }
    }

    return "";
}
string checkValue(string lexeme) // 0@5 5@0 5
{
    int state = 1;
    char ch;
    bool lastChar = false;
    string output;
    bool isZ = false;

    for (int i = 0; i <= lexeme.length() + 1; i++)
    {
        if (i == lexeme.length())
            lastChar = true;
        ch = lexeme[i];

        switch (state)
        {
        case 0: // trap
            return "error";
            break;
        case 1:
            if ((ch >= '0' && ch <= '9') || ch == '@')
            {
                if (ch == '@')
                {
                    if (isZ)
                        state = 0;
                    else
                    {
                        isZ = true;
                        state = 1;
                    }
                }
                else
                    state = 1;
            }
            else if (lastChar)
            {
                lastChar = false;
                return "t_@";
            }
            else
                state = 0;
            break;
        }
    }

    return "";
}
void lexicalAnalyzer(string lexeme, int row, int column, ofstream &outputToken)
{
    string state;

    while (true)
    {
        state = checkKeyWord(lexeme);
        if (state == "error")
            state = checkShenase(lexeme);
        else
            break;
        if (state == "error")
            state = checkSplitter(lexeme);
        else
            break;
        if (state == "error")
            state = checkOperand(lexeme);
        else
            break;
        if (state == "error")
            state = checkValue(lexeme);
        break;
    }

    if (state == "error")
    {
        lexicalError = true;
        cout << row << ":" << column << " \t|\t" << lexeme << endl;
    }
    else if (!lexicalError)
    {
        tokenCount++;
        outputToken
            << state << endl
            << row << endl
            << column << endl;
    }
}

int main()
{
    string inputFileName, temp;
    inputFileName = "./tests/";
    cout << "\n\n-File extension must be .sadrayavar" << endl
         << "-Dont type the extension part" << endl
         << "-Input File must be in the tests folder" << endl
         << "-example:\tsyntatic" << endl
         << endl
         << "Enter your input file name:\t";
    cin >> temp;
    cout << "\n\n";
    inputFileName += temp;
    inputFileName += ".sadrayavar";

    // input the file
    ifstream inputFile(inputFileName);
    string inputText;
    ofstream outputToken("tokenList.txt");
    string tokens;

    // detect lexemes and send them to the lexical analyzer
    string lexeme;
    int row = 1, column = 1;
    while (getline(inputFile, inputText))
    {
        // bayad moshaxas konim kodam lexeme ha dar mian matn tashxis dade mishavand. anhayi ke beyne matn tashxis dade mishavand:
        // dishdadadadam   eq   pl   mi   mu   di   ?=   ?>   ?<   -   /   \   "   '

        for (int i = 0; i < inputText.length(); i++)
        {
            // detects dishdadadadam  in the text and send it
            if (inputText[i] == 'd' &&
                inputText[i + 1] == 'i' &&
                inputText[i + 2] == 's' &&
                inputText[i + 3] == 'h' &&
                inputText[i + 4] == 'd' &&
                inputText[i + 5] == 'a' &&
                inputText[i + 6] == 'd' &&
                inputText[i + 7] == 'a' &&
                inputText[i + 8] == 'd' &&
                inputText[i + 9] == 'a' &&
                inputText[i + 10] == 'd' &&
                inputText[i + 11] == 'a' &&
                inputText[i + 12] == 'm')
            {
                if (lexeme != "")
                    lexicalAnalyzer(lexeme, row, i, outputToken);
                lexeme = "";

                lexicalAnalyzer("dishdadadadam", row, i, outputToken);
                i += 12;
            }
            // detects eq pl mi mu di ?= ?> ?<  in the text and send it
            else if ((inputText[i] == 'e' && inputText[i + 1] == 'q') ||
                     (inputText[i] == 'p' && inputText[i + 1] == 'l') ||
                     (inputText[i] == 'm' && inputText[i + 1] == 'i') ||
                     (inputText[i] == 'm' && inputText[i + 1] == 'u') ||
                     (inputText[i] == 'd' && inputText[i + 1] == 'i' && inputText[i + 2] != 's') ||
                     (inputText[i] == '?' && inputText[i + 1] == '>') ||
                     (inputText[i] == '?' && inputText[i + 1] == '=') ||
                     (inputText[i] == '?' && inputText[i + 1] == '<'))
            {
                string temp = "";
                temp += inputText[i];
                temp += inputText[i + 1];
                lexicalAnalyzer(temp, row, i, outputToken);
                i += 2;
            }
            // detects / \ " -  in the text and send it
            else if (inputText[i] == '/' || inputText[i] == '\\' || inputText[i] == '"' || inputText[i] == '\'')
            {
                string temp = "";
                temp += inputText[i];
                lexicalAnalyzer(temp, row, i, outputToken);
                i++;
            }
            // detects space in the text but doesnt send it
            else if (inputText[i] == ' ')
            {
                if (lexeme == "")
                    continue;
                lexicalAnalyzer(lexeme, row, i, outputToken);
                lexeme = "";
            }
            else
                lexeme += inputText[i];
        }
        // send lexeme to analyzer when newline detected
        if (lexeme != "")
        {
            lexicalAnalyzer(lexeme, row, inputText.length(), outputToken);
            lexeme = "";
        }
        row++;
    }
    inputFile.close();
    outputToken.close();

    if (lexicalError)
    {
        cout << "\nFix the Lexical errors that are included abow and run the program again\n\n";
        return 0;
    }

    // read tokens and send them to the syntatic analyzer
    string tokenList[tokenCount][3];
    ifstream inputToken("tokenList.txt");
    int index = 0, indector = 0, some = 0;
    while (getline(inputToken, tokens))
    {
        tokenList[index][indector++ % 3] = tokens;
        if (++some == 3)
        {
            some = 0;
            index++;
        }
    }
    inputToken.close();
    remove("tokenList.txt");

    // // display token list(debugging)
    // for (int i = 0; i < tokenCount; i++)
    //     cout << tokenList[i][0] << "\t\t" << tokenList[i][1] << ":" << tokenList[i][2] << endl;
    // cout << endl;

    lookahead = tokenList[tokenIndex++][0];
    dasturat(tokenList);
    cout << "your code is great!";
}