bignum_mul(ScmBignum *bx, ScmBignum *by)
{
    u_int i;
    ScmBignum *br = make_bignum(bx->size + by->size);
    for (i=0; i<by->size; i++) {
        bignum_mul_word(br, bx, by->values[i], i);
    }
    br->sign = bx->sign * by->sign;
    return br;
}
