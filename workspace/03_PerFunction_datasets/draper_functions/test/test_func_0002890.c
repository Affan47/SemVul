lj_ir_knumint(jit_State *J, lua_Number n)
{
  int32_t k;
  if (numistrueint(n, &k))
    return lj_ir_kint(J, k);
  else
    return lj_ir_knum(J, n);
}
