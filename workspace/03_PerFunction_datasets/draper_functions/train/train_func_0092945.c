ap_texpr1_copy(ap_texpr1_t* expr)
{
  if (!expr) return NULL;
  return ap_texpr1_of_texpr0(expr->env,ap_texpr0_copy(expr->texpr0));
}
