ap_coeff_neg(ap_coeff_t* a, ap_coeff_t* b)
{
  ap_coeff_set(a,b);
  switch(b->discr){
  case AP_COEFF_SCALAR:
    ap_scalar_neg(a->val.scalar,b->val.scalar);
    break;
  case AP_COEFF_INTERVAL:
    ap_interval_neg(a->val.interval,b->val.interval);
    break;
  default:
    abort();
  }
}
