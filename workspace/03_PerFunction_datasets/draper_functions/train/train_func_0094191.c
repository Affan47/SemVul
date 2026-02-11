Scm_BitsLowest0(const ScmBits *bits, int start, int end)
{
    int sw = start/SCM_WORD_BITS;
    int sb = start%SCM_WORD_BITS;
    int ew = (end-1)/SCM_WORD_BITS;
    int eb = end%SCM_WORD_BITS;

    if (start == end) return -1;
    if (ew == sw) {
        u_long w = ~bits[sw] & SCM_BITS_MASK(sb, eb);
        if (w) return lowest(w) + sw*SCM_WORD_BITS;
        else   return -1;
    } else {
        u_long w = ~bits[sw] & SCM_BITS_MASK(sb, 0);
        if (w) return lowest(w) + sw*SCM_WORD_BITS;
        for (;sw < ew; sw++) {
            if (~bits[sw]) return lowest(~bits[sw])+sw*SCM_WORD_BITS;
        }
        w = ~bits[ew] & SCM_BITS_MASK(0, eb);
        if (w) return lowest(w) + ew*SCM_WORD_BITS;
        return -1;
    }
}
