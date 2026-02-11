find_rtx_in_ldst (rtx x)
{
  struct ls_expr e;
  void **slot;
  if (!pre_ldst_table)
    return NULL;
  e.pattern = x;
  slot = htab_find_slot (pre_ldst_table, &e, NO_INSERT);
  if (!slot || ((struct ls_expr *)*slot)->invalid)
    return NULL;
  return (struct ls_expr *) *slot;
}
