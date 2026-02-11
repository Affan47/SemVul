ap_scalar_inv(ap_scalar_t* a, ap_scalar_t* b)
{
  ap_scalar_reinit(a,b->discr);
  switch(b->discr){
  case AP_SCALAR_MPQ:
    mpq_inv(a->val.mpq,b->val.mpq);
    break;
  case AP_SCALAR_DOUBLE:
    a->val.dbl = 1.0/b->val.dbl;
    break;
  case AP_SCALAR_MPFR:
    if (a!=b) mpfr_set_prec(a->val.mpfr,mpfr_get_prec(b->val.mpfr));
    mpfr_ui_div(a->val.mpfr,1,b->val.mpfr,GMP_RNDU);
    break;
  default:
    abort();
  }
}
