Bignum_To_Long (Object x) {
    unsigned long int ret = 0;
    int i, shift = 0, size = BIGNUM(x)->usize;
    int digits = sizeof(long)/2;

    if (size > digits)
err:
        Primitive_Error ("integer out of range: ~s", x);
    for (i = 0; i < digits && i < size; i++, shift += 16)
        ret |= (unsigned long int)BIGNUM(x)->data[i] << shift;
    if (Truep (BIGNUM(x)->minusp)) {
        if (ret > (~(unsigned long int)0 >> 1) + 1)
            goto err;
        return -ret;
    } else {
        if (ret > ~(unsigned long int)0 >> 1)
            goto err;
        return ret;
    }
}
