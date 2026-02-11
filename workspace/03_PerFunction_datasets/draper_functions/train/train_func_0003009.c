ap_texpr1_substitute(ap_texpr1_t* a, ap_var_t var, ap_texpr1_t *dst)
{
  if (!a || !dst || !ap_environment_is_eq(a->env, dst->env))
    return NULL;
  ap_dim_t dim = ap_environment_dim_of_var(a->env,var);
  if (dim==AP_DIM_MAX)
    return NULL;
  return ap_texpr1_of_texpr0(a->env,
			     ap_texpr0_substitute(a->texpr0,dim,dst->texpr0));
}
