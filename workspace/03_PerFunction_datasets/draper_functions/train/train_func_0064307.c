poly_approximate_10(ap_manager_t* man, pk_t* po)
{
  bool change;
  pk_internal_t* pk = (pk_internal_t*)man->internal;

  poly_chernikova(man,po,"of the argument");
  if (pk->exn){
    pk->exn = AP_EXC_NONE;
    return;
  }
  if (!po->C && !po->F){
    return;
  }
  assert(po->C && po->F);
  change = matrix_approximate_constraint_10(pk, po->C, po->F);
  if (change){
    if (po->F) matrix_free(po->F);
    if (po->satC) satmat_free(po->satC);
    if (po->satF) satmat_free(po->satF);
    po->F = NULL;
    po->satC = NULL;
    po->satF = NULL;
    man->result.flag_exact = false;
  }
  else {
     man->result.flag_exact = true;
  }
}
