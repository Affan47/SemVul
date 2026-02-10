disqualify_base_of_expr (tree t, const char *reason)
{
  t = get_base_address (t);
  if (t
      && sra_mode == SRA_MODE_EARLY_IPA
      && TREE_CODE (t) == MEM_REF)
    t = get_ssa_base_param (TREE_OPERAND (t, 0));

  if (t && DECL_P (t))
    disqualify_candidate (t, reason);
}
