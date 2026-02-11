strip_label()
{
    int start;

    yytext[strlen(yytext)-1] = 0;

    start = 0;
    while ((yytext[start] == ' ') || (yytext[start] == '\t')) start++;
    return &yytext[start];
}
