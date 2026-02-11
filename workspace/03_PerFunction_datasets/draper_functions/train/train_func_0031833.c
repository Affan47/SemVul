parse_id(char *p, char **save)
{
char	*b;

    while (isspace(*p)) if (*p++ == '\n') rescan_lineno++;
    if (!isalpha(*p) && *p != '_') return 0;
    b = p;
    while (isalnum(*p) || *p == '_' || *p == '$') p++;
    if (save) {
	*save = cache_tag(b, p-b); }
    return p;
}
