ldst_entry (rtx x)
{
  int do_not_record_p = 0;
  struct ls_expr * ptr;
  unsigned int hash;

  hash = hash_expr_1 (x, GET_MODE (x), & do_not_record_p);

  for (ptr = pre_ldst_mems; ptr != NULL; ptr = ptr->next)
    if (ptr->hash_index == hash && expr_equiv_p (ptr->pattern, x))
      return ptr;

  ptr = xmalloc (sizeof (struct ls_expr));

  ptr->next         = pre_ldst_mems;
  ptr->expr         = NULL;
  ptr->pattern      = x;
  ptr->pattern_regs = NULL_RTX;
  ptr->loads        = NULL_RTX;
  ptr->stores       = NULL_RTX;
  ptr->reaching_reg = NULL_RTX;
  ptr->invalid      = 0;
  ptr->index        = 0;
  ptr->hash_index   = hash;
  pre_ldst_mems     = ptr;

  return ptr;
}
