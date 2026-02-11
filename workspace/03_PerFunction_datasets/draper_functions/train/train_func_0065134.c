permute_ip(des_cblock inblock, DES_KEY * key, des_cblock outblock)
{
	register unsigned char *ib, *ob;
	register unsigned char *p, *q;
	register int j;


	memset(outblock, '\0', 8);

	ib = inblock;
	for (j = 0; j < 16; j += 2, ib++) {
		ob = outblock;
		p = key->iperm[j][(*ib >> 4) & 0xf];
		q = key->iperm[j + 1][*ib & 0xf];

		*ob++ |= *p++ | *q++;
		*ob++ |= *p++ | *q++;
		*ob++ |= *p++ | *q++;
		*ob++ |= *p++ | *q++;
		*ob++ |= *p++ | *q++;
		*ob++ |= *p++ | *q++;
		*ob++ |= *p++ | *q++;
		*ob++ |= *p++ | *q++;
	}
}
