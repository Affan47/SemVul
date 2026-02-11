maxpy(Integer& res, const Integer& a, const Integer& x, const Integer& b)
{
    if (isZero(a) || isZero(x)) return res=b;
    if (&res == &b) return Integer::maxpyin(res,a,x);
    mpz_mul( (mpz_ptr)&res.gmp_rep, (mpz_srcptr)&a.gmp_rep, (mpz_srcptr)&x.gmp_rep);
    mpz_sub( (mpz_ptr)&res.gmp_rep, (mpz_srcptr)&b.gmp_rep, (mpz_ptr)&res.gmp_rep);
	return res;
}
