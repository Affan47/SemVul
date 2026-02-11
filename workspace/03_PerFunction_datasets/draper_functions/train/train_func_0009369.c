pk_is_bottom(ap_manager_t* man, pk_t* po)
{
  pk_internal_t* pk = pk_init_from_manager(man,AP_FUNID_IS_BOTTOM);
  if (!po->C && !po->F){
    man->result.flag_exact = man->result.flag_best = true;
    return true;
  }
  if (po->F){
      man->result.flag_exact = man->result.flag_best =
	(po->intdim==0);
      return false;
  }
  else {
    if (pk->funopt->algorithm<0){
      man->result.flag_exact = man->result.flag_best = false;
      return (po->C ? false : true);
    }
    else {
      poly_chernikova(man,po,NULL);
      if (pk->exn){
	man->result.flag_exact = man->result.flag_best = false;
	pk->exn = AP_EXC_NONE;
	return false;
      }
      man->result.flag_exact = man->result.flag_best =
	po->intdim>0 && po->F ? false : true;
      return (po->F == NULL);
    }
  }
}
