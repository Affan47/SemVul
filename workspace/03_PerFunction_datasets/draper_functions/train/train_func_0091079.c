xsh_pre_3d_init(xsh_pre_3d * pre, cpl_propertylist * header)
{


  XSH_ASSURE_NOT_NULL(pre);
  XSH_ASSURE_NOT_NULL(header);


  pre->data_header = header;


  check( pre->naxis1 = xsh_pfits_get_naxis1(pre->data_header));
  check( pre->naxis2 = xsh_pfits_get_naxis2(pre->data_header));
  check( pre->naxis3 = xsh_pfits_get_naxis3(pre->data_header));

  cleanup:
    return;
}
