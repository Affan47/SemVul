ap_coeff_init_set(ap_coeff_t* coeff, ap_coeff_t* coeff2)
{
  coeff->discr = coeff2->discr;
  switch (coeff2->discr){
  case AP_COEFF_SCALAR:
    coeff->val.scalar = ap_scalar_alloc_set(coeff2->val.scalar);
    break;
  case AP_COEFF_INTERVAL:
    coeff->val.interval = ap_interval_alloc_set(coeff2->val.interval);
    break;
  }
}
