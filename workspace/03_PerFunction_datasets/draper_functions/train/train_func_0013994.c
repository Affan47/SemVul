Bignum_To_Unsigned_Long (Object x) {
    unsigned long int ret = 0;
    int i, shift = 0, size = BIGNUM(x)->usize;
    int digits = sizeof(long)/2;

    if (size > digits || Truep (BIGNUM(x)->minusp))
        Primitive_Error ("integer out of range: ~s", x);
    for (i = 0; i < digits && i < size; i++, shift += 16)
        ret |= (unsigned long int)BIGNUM(x)->data[i] << shift;
    return ret;
}
