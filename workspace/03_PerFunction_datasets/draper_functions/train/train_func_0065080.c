yyerror(s)
char *s;
{
    if (outmess(s,curfilenum(),yylineno))
	errcount++;
}
