bv_recount(BitVector * bv)
{

    int i, c = 0;
    uchar *bytes = (uchar *)bv->bits;
    const int num_bytes = (((bv->size >> 5) + 1) << 2);
    if (bv->extends_as_ones) {
        for (i = 0; i < num_bytes; i++) {
            c += BYTE_COUNTS[~(bytes[i]) & 0xFF];
        }
    }
    else {
        for (i = 0; i < num_bytes; i++) {
            c += BYTE_COUNTS[bytes[i]];
        }
    }
    bv->count = c;
    return c;
}
