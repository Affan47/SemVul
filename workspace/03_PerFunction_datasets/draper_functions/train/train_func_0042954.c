get_def_for_expr_class (tree name, enum tree_code_class tclass)
{
  gimple def_stmt;

  if (TREE_CODE (name) != SSA_NAME)
    return NULL;

  def_stmt = get_gimple_for_ssa_name (name);
  if (!def_stmt
      || TREE_CODE_CLASS (gimple_assign_rhs_code (def_stmt)) != tclass)
    return NULL;

  return def_stmt;
}
