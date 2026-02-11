ap_quasilinearize_linexpr0(ap_manager_t* man,
					  void* abs,
					  ap_linexpr0_t* linexpr0,
					  bool* pexact,
					  ap_scalar_discr_t discr)
{
  if (ap_linexpr0_is_quasilinear(linexpr0)){
    *pexact = true;
    return linexpr0;
  }
  else {
    switch (discr){
    case AP_SCALAR_MPQ:
      return ap_quasilinearize_linexpr0_MPQ(man,abs,linexpr0,pexact);
    case AP_SCALAR_DOUBLE:
      return ap_quasilinearize_linexpr0_D(man,abs,linexpr0,pexact);
    case AP_SCALAR_MPFR:
      return ap_quasilinearize_linexpr0_MPFR(man,abs,linexpr0,pexact);
    default:
      abort();
    }
  }
}
