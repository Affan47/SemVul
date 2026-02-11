CORD_str(CORD x, size_t start, CORD s)
{
    CORD_pos xpos;
    size_t xlen = CORD_len(x);
    size_t slen;
    register size_t start_len;
    const char * s_start;
    unsigned long s_buf = 0;
    unsigned long x_buf = 0;


    unsigned long mask = 0;
    register size_t i;
    register size_t match_pos;

    if (s == CORD_EMPTY) return(start);
    if (CORD_IS_STRING(s)) {
        s_start = s;
        slen = strlen(s);
    } else {
        s_start = CORD_to_char_star(CORD_substr(s, 0, sizeof(unsigned long)));
        slen = CORD_len(s);
    }
    if (xlen < start || xlen - start < slen) return(CORD_NOT_FOUND);
    start_len = slen;
    if (start_len > sizeof(unsigned long)) start_len = sizeof(unsigned long);
    CORD_set_pos(xpos, x, start);
    for (i = 0; i < start_len; i++) {
        mask <<= 8;
        mask |= 0xff;
        s_buf <<= 8;
        s_buf |= (unsigned char)s_start[i];
        x_buf <<= 8;
        x_buf |= (unsigned char)CORD_pos_fetch(xpos);
        CORD_next(xpos);
    }
    for (match_pos = start; ; match_pos++) {
        if ((x_buf & mask) == s_buf) {
            if (slen == start_len ||
                CORD_ncmp(x, match_pos + start_len,
                      s, start_len, slen - start_len) == 0) {
                return(match_pos);
            }
        }
    if ( match_pos == xlen - slen ) {
        return(CORD_NOT_FOUND);
    }
        x_buf <<= 8;
        x_buf |= (unsigned char)CORD_pos_fetch(xpos);
        CORD_next(xpos);
    }
}
