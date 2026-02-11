box_assign_texpr_array(ap_manager_t* man,
			      bool destructive,
			      box_t* a,
			      ap_dim_t* tdim,
			      ap_texpr0_t** texpr,
			      size_t size,
			      box_t* dest)
{
  size_t i;
  box_t* res;
  box_internal_t* intern = man->internal;

  if (a->p==NULL || (dest && dest->p==NULL)){
    man->result.flag_best = true;
    man->result.flag_exact = true;
    return destructive ? a : box_copy(man,a);
  }
  if (size==1){
    res = destructive ? a : box_copy(man,a);
    itv_eval_ap_texpr0(intern->itv,res->p[tdim[0]],texpr[0],a->p);
  }
  else {
    res = box_copy(man,a);
    for (i=0;i<size;i++){
      itv_eval_ap_texpr0(intern->itv,res->p[tdim[i]],texpr[i],a->p);
    }
    if (destructive) box_free(man,a);
  }
  if (dest)
    res = box_meet(man,true,res,dest);
  man->result.flag_best = false;
  man->result.flag_exact = false;
  return res;
}
