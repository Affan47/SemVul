Switch_On_Term_Var_Atm_Lst(CodePtr c_var, CodePtr c_atm, CodePtr c_lst)
{
  WamWord word, tag_mask;

  DEREF(A(0), word, tag_mask);
  A(0) = word;

  if (tag_mask == TAG_LST_MASK)
    return c_lst;

  if (tag_mask == TAG_ATM_MASK)
    return c_atm;

  if (tag_mask == TAG_REF_MASK
#ifndef NO_USE_FD_SOLVER
      || tag_mask == TAG_FDV_MASK
#endif
      )
    return c_var;

  return ALTB(B);
}
