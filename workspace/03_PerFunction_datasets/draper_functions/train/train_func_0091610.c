ap_abstract0_widening(ap_manager_t* man,
				      ap_abstract0_t* a1, ap_abstract0_t* a2)
{
  if (ap_abstract0_checkman2(AP_FUNID_WIDENING,man,a1,a2) &&
      ap_abstract0_check_abstract2(AP_FUNID_WIDENING,man,a1,a2)){
    void* (*ptr)(ap_manager_t*,...) = man->funptr[AP_FUNID_WIDENING];
    void* value = ptr(man,a1->value,a2->value);
    return ap_abstract0_cons(man,value);
  }
  else {
    ap_dimension_t dimension = _ap_abstract0_dimension(a1);
    return ap_abstract0_top(man,
			    dimension.intdim,
			    dimension.realdim);
  }
}
