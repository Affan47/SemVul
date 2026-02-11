getbits(PMPSTR mp, int number_of_bits)
{
    unsigned long rval;

    if (number_of_bits <= 0 || !mp->wordpointer)
        return 0;

    {
        rval = mp->wordpointer[0];
        rval <<= 8;
        rval |= mp->wordpointer[1];
        rval <<= 8;
        rval |= mp->wordpointer[2];
        rval <<= mp->bitindex;
        rval &= 0xffffff;

        mp->bitindex += number_of_bits;

        rval >>= (24 - number_of_bits);

        mp->wordpointer += (mp->bitindex >> 3);
        mp->bitindex &= 7;
    }
    return rval;
}
