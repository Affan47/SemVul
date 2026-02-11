equality_check(pk_internal_t* pk, pkeq_t* po)
{
  if (!poly_check(pk,po)) return false;
  if ((po->C && !po->F) || (!po->C && po->F)){
     fprintf(stderr,"equality_check: po->C && !po->F || !po->C && po->F: not in canonical form: \n");
     return false;
  }
  if (po->C && po->C->nbrows != po->nbeq+1){
      fprintf(stderr,"equality_check: po->C->nbrows != po->nbeq+1\n");
     return false;
  }
  if (po->F && po->F->nbrows != po->nbline+1){
      fprintf(stderr,"equality_check: po->F->nbrows != po->nbline+1\n");
     return false;
  }
  return true;
}
