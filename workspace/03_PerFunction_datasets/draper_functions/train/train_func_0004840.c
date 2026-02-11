parse_var(struct libinjection_sqli_state * sf)
{
    size_t xlen;
    const char *cs = sf->s;
    const size_t slen = sf->slen;
    size_t pos = sf->pos + 1;


    if (pos < slen && cs[pos] == '@') {
        pos += 1;
        sf->current->count = 2;
    } else {
        sf->current->count = 1;
    }


    if (pos < slen) {
        if (cs[pos] == '`') {
            sf->pos = pos;
            pos = parse_tick(sf);
            sf->current->type = TYPE_VARIABLE;
            return pos;
        } else if (cs[pos] == CHAR_SINGLE || cs[pos] == CHAR_DOUBLE) {
            sf->pos = pos;
            pos = parse_string(sf);
            sf->current->type = TYPE_VARIABLE;
            return pos;
        }
    }


    xlen = strlencspn(cs + pos, slen - pos,
                     " <>:\\?=@!#~+-*/&|^%(),';\t\n\v\f\r'`\"");
    if (xlen == 0) {
        st_assign(sf->current, TYPE_VARIABLE, pos, 0, cs + pos);
        return pos;
    } else {
        st_assign(sf->current, TYPE_VARIABLE, pos, xlen, cs + pos);
        return pos + xlen;
    }
}
