get_tag()
{
    register int c;
    int t_lineno = lineno;
    char *t_line = dup_line();
    char *t_cptr = t_line + (cptr - line);

    ++cptr;
    c = nextc();
    if (c == EOF) unexpected_EOF();
    if (!isalpha(c) && c != '_' && c != '$')
	illegal_tag(t_lineno, t_line, t_cptr);

    cinc = 0;
    do { cachec(c); c = *++cptr; } while (IS_IDENT(c));

    c = nextc();
    if (c == EOF) unexpected_EOF();
    if (c != '>')
	illegal_tag(t_lineno, t_line, t_cptr);
    ++cptr;

    FREE(t_line);
    havetags = 1;
    return cache_tag(cache, cinc);
}
