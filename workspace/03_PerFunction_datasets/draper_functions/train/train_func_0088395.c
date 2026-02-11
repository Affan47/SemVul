internal_mod(BignumInt *a, int alen,
			 BignumInt *m, int mlen,
			 BignumInt *quot, int qshift)
{
    BignumInt m0, m1;
    unsigned int h;
    int i, k;

    m0 = m[0];
    if (mlen > 1)
	m1 = m[1];
    else
	m1 = 0;

    for (i = 0; i <= alen - mlen; i++) {
	BignumDblInt t;
	unsigned int q, r, c, ai1;

	if (i == 0) {
	    h = 0;
	} else {
	    h = a[i - 1];
	    a[i - 1] = 0;
	}

	if (i == alen - 1)
	    ai1 = 0;
	else
	    ai1 = a[i + 1];


	if (h >= m0) {


	    q = BIGNUM_INT_MASK;
	} else {


	    BignumInt tmplo = a[i];
	    DIVMOD_WORD(q, r, h, tmplo, m0);


	    t = MUL_WORD(m1, q);
	    if (t > ((BignumDblInt) r << BIGNUM_INT_BITS) + ai1) {
		q--;
		t -= m1;
		r = (r + m0) & BIGNUM_INT_MASK;
		if (r >= (BignumDblInt) m0 &&
		    t > ((BignumDblInt) r << BIGNUM_INT_BITS) + ai1) q--;
	    }
	}


	c = 0;
	for (k = mlen - 1; k >= 0; k--) {
	    t = MUL_WORD(q, m[k]);
	    t += c;
	    c = (unsigned)(t >> BIGNUM_INT_BITS);
	    if ((BignumInt) t > a[i + k])
		c++;
	    a[i + k] -= (BignumInt) t;
	}


	if (c != h) {
	    t = 0;
	    for (k = mlen - 1; k >= 0; k--) {
		t += m[k];
		t += a[i + k];
		a[i + k] = (BignumInt) t;
		t = t >> BIGNUM_INT_BITS;
	    }
	    q--;
	}
	if (quot)
	    internal_add_shifted(quot, q, qshift + BIGNUM_INT_BITS * (alen - mlen - i));
    }
}
