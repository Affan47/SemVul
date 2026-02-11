pk_bound_texpr(ap_manager_t* man,
			      pk_t* po,
			      ap_texpr0_t* expr)
{
  itv_t itv1,itv2;
  itv_t* env;
  ap_interval_t* interval;
  pk_internal_t* pk = pk_init_from_manager(man,AP_FUNID_BOUND_TEXPR);

  interval = ap_interval_alloc();
  ap_interval_reinit(interval,AP_SCALAR_MPQ);
  if (pk->funopt->algorithm>0)
    poly_chernikova(man,po,NULL);
  else
    poly_obtain_F(man,po,NULL);

  if (pk->exn){
    pk->exn = AP_EXC_NONE;
    ap_interval_set_top(interval);
    return interval;
  }
  if (!po->F){
    ap_interval_set_bottom(interval);
    man->result.flag_exact = man->result.flag_best = true;
    return interval;
  }
  env = matrix_to_box(pk,po->F);
  itv_intlinearize_ap_texpr0(pk->itv,&pk->poly_itv_linexpr,
			     expr,env,po->intdim);
  itv_init(itv1); itv_init(itv2);
  matrix_bound_itv_linexpr(pk,itv1,&pk->poly_itv_linexpr,po->F);
  itv_eval_ap_texpr0(pk->itv,itv2,expr,env);
  itv_meet(pk->itv,itv1,itv1,itv2);
  ap_interval_set_itv(pk->itv,interval,itv1);
  itv_clear(itv1); itv_clear(itv2);
  itv_array_free(env,po->intdim+po->realdim);
  man->result.flag_exact = man->result.flag_best = ap_texpr0_is_interval_linear(expr);

  return interval;
}
