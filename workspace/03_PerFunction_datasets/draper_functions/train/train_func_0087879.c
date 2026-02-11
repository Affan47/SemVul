mpz_mod(mpz_ptr r, mpz_ptr z, mpz_ptr m)
{
	int err;

	if (r == m)
		_mpz_clone_stack(m);
	if ((err = mpz_tdiv_r(r, z, m)) != SBN_OK)
		return err;
	if (r->l && z->s) {
		if (m->s) {
			if ((err = mpz_sub(r, r, m)) != SBN_OK)
				return err;
		} else {
			if ((err = mpz_add(r, r, m)) != SBN_OK)
				return err;
		}
	}
	return SBN_OK;
}
