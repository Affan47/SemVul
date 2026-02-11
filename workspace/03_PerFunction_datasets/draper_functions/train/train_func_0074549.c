scm_to_mpz (SCM val, mpz_t rop)
{
  if (SCM_I_INUMP (val))
    mpz_set_si (rop, SCM_I_INUM (val));
  else if (SCM_BIGP (val))
    mpz_set (rop, SCM_I_BIG_MPZ (val));
  else
    scm_wrong_type_arg_msg (NULL, 0, val, "exact integer");
}
