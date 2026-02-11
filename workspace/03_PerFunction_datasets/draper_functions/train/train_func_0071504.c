re_insert(EditLine *el __attribute__((__unused__)),
    Char *d, int dat, int dlen, Char *s, int num)
{
	Char *a, *b;

	if (num <= 0)
		return;
	if (num > dlen - dat)
		num = dlen - dat;

	ELRE_DEBUG(1,
	    (__F, "re_insert() starting: %d at %d max %d, d == \"%s\"\n",
	    num, dat, dlen, ct_encode_string(d)));
	ELRE_DEBUG(1, (__F, "s == \"%s\"\n", ct_encode_string(s)));


	if (num > 0) {
		b = d + dlen - 1;
		a = b - num;
		while (a >= &d[dat])
			*b-- = *a--;
		d[dlen] = '\0';
	}

	ELRE_DEBUG(1, (__F,
		"re_insert() after insert: %d at %d max %d, d == \"%s\"\n",
		num, dat, dlen, ct_encode_string(d)));
	ELRE_DEBUG(1, (__F, "s == \"%s\"\n", ct_encode_string(s)));


	for (a = d + dat; (a < d + dlen) && (num > 0); num--)
		*a++ = *s++;

#ifdef notyet


	ELRE_DEBUG(1,
	    (__F, "re_insert() after copy: %d at %d max %d, %s == \"%s\"\n",
	    num, dat, dlen, d, s));
	ELRE_DEBUG(1, (__F, "s == \"%s\"\n", s));
#endif
}
