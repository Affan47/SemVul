mpz_tdiv_qr(mpz_ptr q, mpz_ptr r, mpz_ptr z, mpz_ptr d)
{
	int cmp;
	int err;

	if (d->l == 0)
		return SBN_INVAL;
	if (z == d) {
		err = mpz_set_ui(q, 1);
		if (err != SBN_OK)
			return err;
		mpz_setzero(r);
		return SBN_OK;
	}
	cmp = mpz_cmpabs(z, d);
	if (cmp < 0) {
		err = mpz_set(r, z);
		if (err != SBN_OK)
			return err;
		mpz_setzero(q);
		return SBN_OK;
	} else if (cmp == 0) {
		err = mpz_set_ui(q, 1);
		if (err != SBN_OK)
			return err;
		mpz_setzero(r);
		return SBN_OK;
	}

	if (z == q || z == r)
		_mpz_clone_stack(z);

	if (d == q || d == r)
		_mpz_clone_stack(d);

	q->s = z->s^d->s;
	r->s = z->s;
	return mpz_divi_qr_raw(q, r, z, d->d, d->l);
}
