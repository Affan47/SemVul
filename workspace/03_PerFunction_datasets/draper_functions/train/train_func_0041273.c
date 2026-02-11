init_one(int32_t *lut, int32_t mask)
{
    int bits  = 0;
    int shift = 0;
    int i;

    for (i = 0; i < 32; i++) {
        if (mask & ((int32_t)1 << i))
	    bits++;
        else if (!bits)
	    shift++;
    }

    if (bits > 8)
	for (i = 0; i < 256; i++)
	    lut[i] = (i << (bits + shift - 8));
    else
	for (i = 0; i < 256; i++)
	    lut[i] = (i >> (8 - bits)) << shift;
}
