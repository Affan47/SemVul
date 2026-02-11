G_tokenize(const char *buf, const char *delim)
{
    int i;
    char **tokens;
    char *p;

    i = 0;
    while (!G_index(delim, *buf) && (*buf == ' ' || *buf == '\t'))
	buf++;

    p = G_store(buf);

    tokens = (char **)G_malloc(sizeof(char *));

    while (1) {
	while (!G_index(delim, *p) && (*p == ' ' || *p == '\t'))
	    p++;
	if (*p == 0)
	    break;
	tokens[i++] = p;
	tokens = (char **)G_realloc((char *)tokens, (i + 1) * sizeof(char *));

	while (*p && (G_index(delim, *p) == NULL))
	    p++;
	if (*p == 0)
	    break;
	*p++ = 0;
    }
    tokens[i] = NULL;

    return (tokens);
}
