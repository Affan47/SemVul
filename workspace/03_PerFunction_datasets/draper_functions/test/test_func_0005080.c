fun_so_universal_newline(void *statep, const unsigned char *s, size_t l, unsigned char *o, size_t osize)
{
    unsigned char *sp = statep;
    int len;
    if (s[0] == '\n') {
        if (STATE == NORMAL) {
            NEWLINES_MET |= MET_LF;
        }
        else {
            NEWLINES_MET |= MET_CRLF;
        }
        o[0] = '\n';
        len = 1;
        STATE = NORMAL;
    }
    else {
        len = 0;
        if (STATE == JUST_AFTER_CR) {
            o[0] = '\n';
            len = 1;
            NEWLINES_MET |= MET_CR;
        }
        if (s[0] == '\r') {
            STATE = JUST_AFTER_CR;
        }
        else {
            o[len++] = s[0];
            STATE = NORMAL;
        }
    }

    return len;
}
