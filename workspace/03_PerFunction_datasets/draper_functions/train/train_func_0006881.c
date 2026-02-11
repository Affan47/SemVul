ap_abstract1_sat_interval(ap_manager_t* man, ap_abstract1_t* a,
			       ap_var_t var, ap_interval_t* interval)
{
  ap_dim_t dim;
  bool res;

  dim = ap_environment_dim_of_var(a->env, var);
  if (dim==AP_DIM_MAX){
    ap_abstract1_raise_invalid_var(man,AP_FUNID_SAT_INTERVAL,var);
    man->result.flag_exact = false;
    return false;
  }
  return ap_abstract0_sat_interval(man, a->abstract0, dim, interval);
}
