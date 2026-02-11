ap_abstract0_widening_threshold(ap_manager_t* man,
						ap_abstract0_t* a1,
						ap_abstract0_t* a2,
						ap_lincons0_array_t* array)
{
  void* (*ptr)(ap_manager_t*,...);
  bool (*ptr2)(ap_manager_t*,...);
  void* value;
  size_t i,j,size;
  ap_lincons0_t tmp;

  ap_dimension_t dimension = _ap_abstract0_dimension(a1);
  if (ap_abstract0_checkman2(AP_FUNID_WIDENING,man,a1,a2) &&
      ap_abstract0_check_abstract2(AP_FUNID_WIDENING,man,a1,a2) &&
      ap_abstract0_check_lincons_array(AP_FUNID_WIDENING,man,dimension,array) ){
    ptr = man->funptr[AP_FUNID_WIDENING];
    value = ptr(man,a1->value,a2->value);

    ptr2 = man->funptr[AP_FUNID_SAT_LINCONS];
    size = array->size;
    i = j = 0;
    while (i<size-j){
      if (ptr2(man,a2->value,&array->p[i])){
	i++;
      }
      else {
	j++;
	tmp = array->p[i];
	array->p[i] = array->p[array->size-j];
	array->p[array->size-j] = tmp;
      }
    }
    if (i>0){
      array->size = i;
      ptr = man->funptr[AP_FUNID_MEET_LINCONS_ARRAY];
      value = ptr(man,true,value,array);
      array->size = size;
    }
    return ap_abstract0_cons(man,value);
  }
  else {
    return ap_abstract0_top(man,
			    dimension.intdim,
			    dimension.realdim);
  }
}
