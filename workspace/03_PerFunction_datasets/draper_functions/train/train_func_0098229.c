FindToken(const char *s)
{
    int i;

    for (i = 0; keywords[i].token > 0; i++)
	if (!strcasecmp(s, keywords[i].name)) {
	    yylval = keywords[i].value;
	    return keywords[i].token;
	}
    Die("%s:%d: Unknown keyword `%s'\n", Opt_modedb, line, s);
}
