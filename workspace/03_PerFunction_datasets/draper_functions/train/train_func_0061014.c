yy_1_definition(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_definition\n"));
   if (push(beginRule(findRule(yytext)))->rule.expression)
							    fprintf(stderr, "rule '%s' redefined\n", yytext); ;
}
