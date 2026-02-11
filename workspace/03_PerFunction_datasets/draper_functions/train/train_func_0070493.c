internal_sub(const BignumInt *a, const BignumInt *b,
                         BignumInt *c, int len)
{
    int i;
    BignumDblInt carry = 1;

    for (i = len-1; i >= 0; i--) {
        carry += (BignumDblInt)a[i] + (b[i] ^ BIGNUM_INT_MASK);
        c[i] = (BignumInt)carry;
        carry >>= BIGNUM_INT_BITS;
    }
}
