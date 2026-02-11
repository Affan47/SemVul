ap_reducedproduct_meetjoin(ap_funid_t funid,

						ap_manager_t* manager,
						bool destructive, ap_reducedproduct_t* a1, ap_reducedproduct_t* a2)
{
  ap_reducedproduct_internal_t* intern = get_internal_init2(manager,funid,a1,a2);
  size_t i;
  ap_reducedproduct_t* res;

  res = destructive ? a1 : ap_reducedproduct_alloc(intern->size);

  for (i=0;i<intern->size;i++){
    ap_manager_t* man = intern->tmanagers[i];
    void* (*ptr)(ap_manager_t*,...) = man->funptr[funid];
    res->p[i] = ptr(man,destructive,a1->p[i],a2->p[i]);
    if (funid==AP_FUNID_MEET){
      bool (*is_bottom)(ap_manager_t*,...) = man->funptr[AP_FUNID_IS_BOTTOM];
      if (is_bottom(man,res->p[i])){
	set_bottom(intern,destructive,res,i);
	goto ap_reducedproduct_meetjoin_exit;
      }
    }
  }
  res->reduced = funid==AP_FUNID_JOIN && a1->reduced && a2->reduced;
 ap_reducedproduct_meetjoin_exit:
  collect_results1(manager,funid,res);
  return res;
}
