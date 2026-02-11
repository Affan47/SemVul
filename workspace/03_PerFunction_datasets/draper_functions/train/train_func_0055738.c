ap_abstract1_meetjoin(ap_funid_t funid, ap_manager_t* man, bool destructive, ap_abstract1_t* a1, ap_abstract1_t* a2)
{
  ap_abstract1_t res;
  if (ap_abstract1_check_env2(funid,man,a1,a2)){
    ap_abstract0_t* value = ap_abstract0_meetjoin(funid,man,destructive,a1->abstract0,a2->abstract0);
    res = ap_abstract1_consres(destructive, a1, value);
  }
  else {
    res = ap_abstract1_top(man,a1->env);
    if (destructive) ap_abstract1_clear(man,a1);
  }
  return res;
}
