mpz_clrbit(mpz_ptr z, u_int32_t i)
{
	u_int32_t atom = i >> DIVATOMBITS_SHIFT;
	u_int32_t bit = i & MODATOMBITS_MASK;

	if (atom >= z->l)
		return SBN_OK;
	z->d[atom] &= ~((mpz_atom_t) 1 << bit);
	if (atom == z->l-1)
		mpz_normalize(z);
	return SBN_OK;
}
