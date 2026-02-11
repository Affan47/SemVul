vrp_expr_computes_nonnegative (tree expr, bool *strict_overflow_p)
{
  return (tree_expr_nonnegative_warnv_p (expr, strict_overflow_p)
	  || (TREE_CODE (expr) == SSA_NAME
	      && ssa_name_nonnegative_p (expr)));
}
