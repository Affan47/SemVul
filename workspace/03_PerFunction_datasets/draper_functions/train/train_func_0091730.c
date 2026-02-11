target_for_debug_bind (tree var)
{
  if (!MAY_HAVE_DEBUG_STMTS)
    return NULL_TREE;

  if (TREE_CODE (var) != VAR_DECL
      && TREE_CODE (var) != PARM_DECL)
    return NULL_TREE;

  if (DECL_HAS_VALUE_EXPR_P (var))
    return target_for_debug_bind (DECL_VALUE_EXPR (var));

  if (DECL_IGNORED_P (var))
    return NULL_TREE;

  if (!is_gimple_reg (var))
    {
      if (is_gimple_reg_type (TREE_TYPE (var))
	  && referenced_var_lookup (cfun, DECL_UID (var)) == NULL_TREE)
	return var;
      return NULL_TREE;
    }

  return var;
}
