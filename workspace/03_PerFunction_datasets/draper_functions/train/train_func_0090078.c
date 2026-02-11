parse_word(struct libinjection_sqli_state * sf)
{
    char ch;
    char delim;
    size_t i;
    const char *cs = sf->s;
    size_t pos = sf->pos;
    size_t wlen = strlencspn(cs + pos, sf->slen - pos,
                             " []{}<>:\\?=@!#~+-*/&|^%(),';\t\n\v\f\r\"\240\000");

    st_assign(sf->current, TYPE_BAREWORD, pos, wlen, cs + pos);


    for (i =0; i < sf->current->len; ++i) {
        delim = sf->current->val[i];
        if (delim == '.' || delim == '`') {
            ch = sf->lookup(sf, LOOKUP_WORD, sf->current->val, i);
            if (ch != TYPE_NONE && ch != TYPE_BAREWORD) {

                st_clear(sf->current);


                st_assign(sf->current, ch, pos, i, cs + pos);
                return pos + i;
            }
        }
    }


    if (wlen < LIBINJECTION_SQLI_TOKEN_SIZE) {

        ch = sf->lookup(sf, LOOKUP_WORD, sf->current->val, wlen);
        if (ch == CHAR_NULL) {
            ch = TYPE_BAREWORD;
        }
        sf->current->type = ch;
    }
    return pos + wlen;
}
