ap_abstract1_bound_linexpr(ap_manager_t* man,
					  ap_abstract1_t* a, ap_linexpr1_t* expr)
{
  ap_interval_t* res;

  if (ap_environment_is_eq(a->env,expr->env)){
    res = ap_abstract0_bound_linexpr(man,a->abstract0,expr->linexpr0);
  }
  else {
    ap_dimchange_t* dimchange;
    ap_linexpr0_t* expr0;

    dimchange = ap_environment_dimchange(expr->env,a->env);
    if (dimchange==NULL){
      ap_manager_raise_exception(man,AP_EXC_INVALID_ARGUMENT,AP_FUNID_BOUND_LINEXPR,
				 "the environment of the linear expression is not a subset of the environment of the abstract value");
      res = ap_interval_alloc();
      ap_interval_reinit(res,man->option.scalar_discr);
      ap_interval_set_top(res);
      return res;
    }
    expr0 = ap_linexpr0_add_dimensions(expr->linexpr0,dimchange);
    res = ap_abstract0_bound_linexpr(man,a->abstract0,expr0);
    ap_dimchange_free(dimchange);
    ap_linexpr0_free(expr0);
  }
  return res;
}
