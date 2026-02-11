Scm_BitsCopyX(ScmBits *target, int tstart,
                   ScmBits *src, int sstart, int send)
{
    if (tstart%SCM_WORD_BITS == 0
        && sstart%SCM_WORD_BITS == 0
        && send%SCM_WORD_BITS == 0) {

        int tw = tstart/SCM_WORD_BITS;
        int sw = sstart/SCM_WORD_BITS;
        int ew = send/SCM_WORD_BITS;
        while (sw < ew) target[tw++] = src[sw++];
    } else {

        int t, s;
        for (t=tstart, s=sstart; s < send; t++, s++) {
            if (SCM_BITS_TEST(src, s)) SCM_BITS_SET(target, t);
            else                       SCM_BITS_RESET(target, t);
        }
    }
}
