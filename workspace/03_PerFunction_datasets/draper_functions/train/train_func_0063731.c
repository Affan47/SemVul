ap_texpr1_extend_environment(ap_texpr1_t* expr,
					  ap_environment_t* nenv)
{
  ap_dimchange_t* dimchange = ap_environment_dimchange(expr->env,nenv);
  if (dimchange==NULL)
    return NULL;
  ap_texpr1_t* res = ap_texpr1_extend_environment_dimchange(expr,nenv,dimchange);
  ap_dimchange_free(dimchange);
  return res;
}
