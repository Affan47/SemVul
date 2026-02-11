fori_arg(jit_State *J, const BCIns *fori, BCReg slot,
		     IRType t, int mode)
{
  TRef tr = J->base[slot];
  if (!tr) {
    tr = find_kinit(J, fori, slot, t);
    if (!tr)
      tr = fori_load(J, slot, t, mode);
  }
  return tr;
}
