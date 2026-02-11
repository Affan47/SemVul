ecm_redc_basecase (mpz_ptr r, mpz_ptr c, mpmod_t modulus)
{
  mp_ptr rp;
  mp_ptr cp;
  mp_srcptr np;
  mp_size_t j, nn = modulus->bits / GMP_NUMB_BITS;

  ASSERT(ABSIZ(c) <= 2 * nn);
  ASSERT(ALLOC(c) >= 2 * nn);
  ASSERT(ALLOC(r) >= nn);
  cp = PTR(c);
  rp = PTR(r);
  np = PTR(modulus->orig_modulus);
  for (j = ABSIZ(c); j < 2 * nn; j++)
    cp[j] = 0;

  redc_basecase_n (rp, cp, np, nn, modulus->Nprim);

  MPN_NORMALIZE (rp, nn);
  SIZ(r) = SIZ(c) < 0 ? (int) -nn : (int) nn;
}
