poly_chernikova2(ap_manager_t* man,
		      pk_t* po,
		      char* msg)
{
  pk_internal_t* pk = (pk_internal_t*)man->internal;
  poly_chernikova(man,po,msg);
  if (pk->exn)
    return;
  if (!po->C && !po->F)
    return;
  assert(po->C && po->F);
  if (!poly_is_minimaleps(pk,po)){
    poly_obtain_satF(po);
    bool change = cherni_minimizeeps(pk,po);
    assert((po->status & pk_status_minimaleps) &&
	   (po->status & pk_status_conseps));
    if (change){
      matrix_sort_rows(pk,po->C);
      cherni_minimize(pk, true, po);
      if (pk->exn) goto poly_chernikova2_exit0;
      assert(po->C && po->F);
      po->status = pk_status_consgauss | pk_status_minimaleps;
    }
  }
  assert(poly_is_minimaleps(pk,po));
  return;
 poly_chernikova2_exit0:
  po->status = 0;
  {
    char str[160];
    sprintf(str,"conversion from %s %s\n",
	    po->C ? "constraints to generators" : "generators to constraints",
	    msg);
    ap_manager_raise_exception(man,pk->exn,pk->funid,str);  }
  return;
}
