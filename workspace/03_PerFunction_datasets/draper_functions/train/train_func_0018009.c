libinjection_sqli_init(struct libinjection_sqli_state * sf, const char *s, size_t len, int flags)
{
    if (flags == 0) {
        flags = FLAG_QUOTE_NONE | FLAG_SQL_ANSI;
    }

    memset(sf, 0, sizeof(struct libinjection_sqli_state));
    sf->s        = s;
    sf->slen     = len;
    sf->lookup   = libinjection_sqli_lookup_word;
    sf->userdata = 0;
    sf->flags    = flags;
    sf->current  = &(sf->tokenvec[0]);
}
