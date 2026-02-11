install_str(void)
{	int i, j = 0;
	yylval.s = emalloc(yyleng-1);
	for (i = 1 + (yytext[0] == 'L'); i < yyleng-1; i++)
		if (yytext[i] == '\\')
		{	if (yytext[++i] != '\n')
			{	yylval.s[j++] = convchar(&i);
				i--;
			}
		}
		else
			yylval.s[j++] = yytext[i];
	yylval.s[j] = '\0';
	return STR;
}
