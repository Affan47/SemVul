builtin_save_expr (tree exp)
{
  if (TREE_CODE (exp) == SSA_NAME
      || (TREE_ADDRESSABLE (exp) == 0
	  && (TREE_CODE (exp) == PARM_DECL
	      || (TREE_CODE (exp) == VAR_DECL && !TREE_STATIC (exp)))))
    return exp;

  return save_expr (exp);
}
