ap_abstract0_meetjoin_array(ap_funid_t funid, ap_manager_t* man, ap_abstract0_t** tab, size_t size)
{
  if (ap_abstract0_checkman_array(funid,man,tab,size) &&
      ap_abstract0_check_abstract_array(funid,man,tab,size)){
    size_t i;
    ap_abstract0_t* res;
    void* (*ptr)(ap_manager_t*,...) = man->funptr[funid];
    void** ntab = malloc(size*sizeof(void*));
    for (i=0;i<size;i++) ntab[i] = tab[i]->value;
    res = ap_abstract0_cons(man,ptr(man,ntab,size));
    free(ntab);
    return res;
  }
  else {
    ap_dimension_t dimension = { 0, 0};
    if (size>0){
      dimension = _ap_abstract0_dimension(tab[0]);
    }
    return ap_abstract0_top(man,
			    dimension.intdim,
			    dimension.realdim);
  }
}
