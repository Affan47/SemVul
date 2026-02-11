tokenize(char *p)
{
    char **tokens = NULL;
    int i = 0;

    if (!p || !*p) return NULL;
    while (*p) {
	while (*p && Uisspace(*p)) p++;

	if (!(i % 10)) tokens = xrealloc(tokens, (i+10) * sizeof(char *));


	tokens[i++] = p;
	while (*p && !Uisspace(*p)) p++;


	if (*p) *p++ = '\0';
    }

    if (!(i % 10)) tokens = xrealloc(tokens, (i+1) * sizeof(char *));
    if (!tokens) return NULL;
    tokens[i] = NULL;

    return tokens;
}
