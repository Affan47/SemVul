setup_ip_maskl(void)
{
    int i, j, k, inbit, obit;
    my_u_int32_t *il;

    for (k = 0; k < 8; k++) {
	for (i = 0; i < 256; i++) {
	    *(il = &common[k][i]) = 0L;
	    for (j = 0; j < 8; j++) {
		inbit = 8 * k + j;
		if (i & bits8[j]) {
		    if ((obit = init_perm[inbit]) < 32)
			*il |= bits32[obit];
		}
	    }
	}
    }
}
