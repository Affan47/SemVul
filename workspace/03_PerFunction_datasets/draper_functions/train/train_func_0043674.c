parse_bstring(struct libinjection_sqli_state *sf)
{
    size_t wlen;
    const char *cs = sf->s;
    size_t pos = sf->pos;
    size_t slen = sf->slen;


    if (pos + 2 >= slen || cs[pos+1] !=  '\'') {
        return parse_word(sf);
    }

    wlen = strlenspn(cs + pos + 2, sf->slen - pos - 2, "01");
    if (pos + 2 + wlen  >= slen || cs[pos + 2 + wlen] != '\'') {
        return parse_word(sf);
    }
    st_assign(sf->current, TYPE_NUMBER, pos, wlen + 3, cs + pos);
    return pos + 2 + wlen + 1;
}
