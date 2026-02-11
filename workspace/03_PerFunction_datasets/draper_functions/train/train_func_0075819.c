bignum_lshift(ScmBignum *br, ScmBignum *bx, int amount)
{
    int nwords, nbits, i;
    u_long x;

    nwords = amount / WORD_BITS;
    nbits = amount % WORD_BITS;
    if (nbits == 0) {

        for (i = (int)bx->size-1; i>=0; i--) {
            if ((int)br->size > i+nwords) br->values[i+nwords] = bx->values[i];
        }
        for (i = nwords-1; i>=0; i--) br->values[i] = 0;
    } else {
        if (br->size > bx->size + nwords) {
            br->values[bx->size+nwords] =
                bx->values[bx->size-1]>>(WORD_BITS-nbits);
        }
        for (i = (int)bx->size-1; i > 0; i--) {
            x = (bx->values[i]<<nbits)|(bx->values[i-1]>>(WORD_BITS-nbits));
            if ((int)br->size > i+nwords) br->values[i+nwords] = x;
        }
        br->values[nwords] = bx->values[0]<<nbits;
        for (i = nwords-1; i>=0; i--) br->values[i] = 0;
    }
    if (br != bx) {
        br->sign = bx->sign;
    }
    return br;
}
