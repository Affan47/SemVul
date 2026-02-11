crypto_pow_classic(mpz2_class a, unsigned long p)
{
	mpz2_class rtn;
	rtn = 1;


	for ( ; p > 0 ; p--)
	{
		rtn = rtn * a;
	}
	return rtn;
}
