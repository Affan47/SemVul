fmpz_gcd(fmpz_t output, fmpz_t x1, fmpz_t x2)
{
	ulong size1 = FLINT_ABS(x1[0]);
	ulong size2 = FLINT_ABS(x2[0]);
   mpz_t m1, m2, m0, m_out;
	m1->_mp_d = x1 + 1;
   m2->_mp_d = x2 + 1;
	m1->_mp_alloc = size1;
	m1->_mp_size = size1;
	m2->_mp_alloc = size2;
	m2->_mp_size = size2;
	ulong size_out = FLINT_MAX(size1, size2)+1;
	m0->_mp_d = flint_stack_alloc(size_out);
   m0->_mp_alloc = size_out;
   m0->_mp_size = 0;
	mpz_gcd(m0, m1, m2);
	size_out = m0->_mp_size;
	F_mpn_copy(output + 1, m0->_mp_d, size_out);
	output[0] = size_out;
	flint_stack_release();
}
