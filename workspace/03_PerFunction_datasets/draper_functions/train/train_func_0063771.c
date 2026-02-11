cxx_eval_unary_expression (const constexpr_call *call, tree t,
			   bool allow_non_constant, bool addr,
			   bool *non_constant_p, bool *overflow_p)
{
  tree r;
  tree orig_arg = TREE_OPERAND (t, 0);
  tree arg = cxx_eval_constant_expression (call, orig_arg, allow_non_constant,
					   addr, non_constant_p, overflow_p);
  VERIFY_CONSTANT (arg);
  if (arg == orig_arg)
    return t;
  r = fold_build1 (TREE_CODE (t), TREE_TYPE (t), arg);
  VERIFY_CONSTANT (r);
  return r;
}
