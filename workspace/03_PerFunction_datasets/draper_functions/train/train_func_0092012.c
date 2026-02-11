ap_scalar_alloc_set(ap_scalar_t* b)
{
  ap_scalar_t* a = malloc(sizeof(ap_scalar_t));
  a->discr = b->discr;
  switch(b->discr){
  case AP_SCALAR_DOUBLE:
    a->val.dbl = b->val.dbl;
    break;
  case AP_SCALAR_MPQ:
    a->val.mpq = malloc(sizeof(mpq_t));
    mpq_init(a->val.mpq);
    mpq_set(a->val.mpq,b->val.mpq);
    break;
  case AP_SCALAR_MPFR:
    a->val.mpfr = malloc(sizeof(mpfr_t));
    mpfr_init2(a->val.mpfr,mpfr_get_prec(b->val.mpfr));
    mpfr_set(a->val.mpfr,b->val.mpfr,GMP_RNDU );
    break;
  default:
    abort();
  }
  return a;
}
