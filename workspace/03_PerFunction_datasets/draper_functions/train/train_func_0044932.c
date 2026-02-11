parser_whole_match_p(struct parser_params *parser,
    const char *eos, long len, int indent)
{
    const char *p = lex_pbeg;
    long n;

    if (indent) {
	while (*p && ISSPACE(*p)) p++;
    }
    n = lex_pend - (p + len);
    if (n < 0 || (n > 0 && p[len] != '\n' && p[len] != '\r')) return FALSE;
    return strncmp(eos, p, len) == 0;
}
