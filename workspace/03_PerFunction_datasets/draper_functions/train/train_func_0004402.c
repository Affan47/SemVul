ap_scalar_set(ap_scalar_t* a, ap_scalar_t* b)
{
  if (a==b) return;
  ap_scalar_reinit(a,b->discr);
  switch(b->discr){
  case AP_SCALAR_DOUBLE:
    a->val.dbl = b->val.dbl;
    break;
  case AP_SCALAR_MPQ:
    mpq_set(a->val.mpq,b->val.mpq);
    break;
  case AP_SCALAR_MPFR:
    mpfr_set_prec(a->val.mpfr,mpfr_get_prec(b->val.mpfr));
    mpfr_set(a->val.mpfr,b->val.mpfr,GMP_RNDU );
    break;
  default:
    abort();
  }
}
