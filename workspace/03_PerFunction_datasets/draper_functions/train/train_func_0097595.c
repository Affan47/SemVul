scm_i_normbig (SCM b)
{


  if (mpz_fits_slong_p (SCM_I_BIG_MPZ (b)))
    {
      long val = mpz_get_si (SCM_I_BIG_MPZ (b));
      if (SCM_FIXABLE (val))
        b = SCM_I_MAKINUM (val);
    }
  return b;
}
