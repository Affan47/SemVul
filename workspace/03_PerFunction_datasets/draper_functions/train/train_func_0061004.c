float_init(void)
{
	int n, i, l;
	bignum_t *b;
	uint64 *xp, *zp, k;


	five[0].l = l = 0;
	five[0].d[0] = 5;
	for (n = MAX_FIVE-1, b = &five[0]; n > 0; n--) {
		xp = &b->d[0];
		b++;
		zp = &b->d[0];
		for (i = l, k = 0; i >= 0; i--)
			MUL(*xp++, 5, *zp++, k);
		if (k != 0)
			*zp = k, l++;
		b->l = l;
		g_assert(b->l < BIGSIZE);
	}

#ifdef FLOAT_DEBUG
	for (n = 1, b = &five[0]; n <= MAX_FIVE; n++) {
		big_shift_left(b++, n, &R);
		print_big(&R);
		putchar('\n');
	}
	fflush(0);
#endif

	float_inited = TRUE;
}
