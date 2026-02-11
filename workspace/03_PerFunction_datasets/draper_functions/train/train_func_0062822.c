yymark()
{
    if (source) free(source);
    source = (char *) calloc(yyleng, sizeof(char));
    if (source) sscanf(yytext, "# %d %s", &yylineno, source);
}
