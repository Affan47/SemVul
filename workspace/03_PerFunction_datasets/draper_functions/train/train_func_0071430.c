mul(Integer& res, const Integer& n1, const Integer& n2)
{
  if (isZero(n1)) return res = Integer::zero;
  if (isZero(n2)) return res = Integer::zero;
  mpz_mul( (mpz_ptr)&res.gmp_rep, (mpz_srcptr)&n1.gmp_rep, (mpz_srcptr)&n2.gmp_rep);
  return res;
}
