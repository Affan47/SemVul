refmpz_jacobi (mpz_srcptr a, mpz_srcptr b)
{
  ASSERT_ALWAYS (mpz_sgn (b) > 0);
  ASSERT_ALWAYS (mpz_odd_p (b));

  return refmpz_kronecker (a, b);
}
