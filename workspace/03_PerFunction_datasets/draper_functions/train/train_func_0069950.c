search_start(struct cache *ca, u8 *pattern)
{
    struct search *s;
    int f = 0;

    if (not(s = malloc(sizeof(*s))))
	goto fail1;

    if (pattern[0] == '!')
	pattern++;
    else
	f = REG_ICASE;

    if (regcomp(s->pattern, pattern, f | REG_NEWLINE) != 0)
	goto fail2;

    s->cache = ca;
    return s;

fail2:
    free(s);
fail1:
    return 0;
}
