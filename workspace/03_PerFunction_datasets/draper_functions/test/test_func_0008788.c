ap_quasilinearize_lincons0_array(ap_manager_t* man,
				 void* abs,
				 ap_lincons0_array_t* array,
				 bool* pexact,
				 ap_scalar_discr_t discr,
				 bool linearize,
				 bool meet)
{
  ap_linexpr_type_t type = ap_lincons0_array_type(array);
  if ((linearize && type==AP_LINEXPR_LINEAR) ||
      type==AP_LINEXPR_QUASILINEAR){
    *pexact = true;
    return *array;
  }
  else {
    switch (discr){
    case AP_SCALAR_MPQ:
      return ap_quasilinearize_lincons0_array_MPQ(man,abs,array,pexact,linearize,meet);
    case AP_SCALAR_DOUBLE:
      return ap_quasilinearize_lincons0_array_D(man,abs,array,pexact,linearize,meet);
    case AP_SCALAR_MPFR:
      return ap_quasilinearize_lincons0_array_MPFR(man,abs,array,pexact,linearize,meet);
    default:
      abort();
    }
  }
}
