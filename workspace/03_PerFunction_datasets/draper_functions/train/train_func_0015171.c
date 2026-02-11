box_widening(ap_manager_t* man,
		    box_t* a1, box_t* a2)
{
  size_t i;
  size_t nbdims;
  box_t* res;

  man->result.flag_best = true;
  man->result.flag_exact = true;
  nbdims = a1->intdim+a1->realdim;
  if (a1->p==NULL){
    return box_copy(man,a2);
  }
  assert(a2->p!=NULL);
  res = box_copy(man,a1);
  for (i=0; i<nbdims; i++){
    itv_widening(res->p[i],a1->p[i],a2->p[i]);
  }
  return res;
}
