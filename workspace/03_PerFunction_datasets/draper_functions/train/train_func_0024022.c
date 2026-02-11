cvt_s(SprintfState *ss, const char *s, int width, int prec,
                 int flags)
{
    int slen;

    if (prec == 0)
        return 0;


    slen = s ? strlen(s) : 6;
    if (prec > 0) {
        if (prec < slen) {
            slen = prec;
        }
    }


    return fill2(ss, s ? s : "(null)", slen, width, flags);
}
