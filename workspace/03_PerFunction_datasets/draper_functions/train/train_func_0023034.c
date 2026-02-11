cxx_eval_builtin_function_call (const constexpr_call *call, tree t,
				bool allow_non_constant, bool addr,
				bool *non_constant_p, bool *overflow_p)
{
  const int nargs = call_expr_nargs (t);
  tree *args = (tree *) alloca (nargs * sizeof (tree));
  tree new_call;
  int i;
  for (i = 0; i < nargs; ++i)
    {
      args[i] = cxx_eval_constant_expression (call, CALL_EXPR_ARG (t, i),
					      allow_non_constant, addr,
					      non_constant_p, overflow_p);
      if (allow_non_constant && *non_constant_p)
	return t;
    }
  if (*non_constant_p)
    return t;
  new_call = build_call_array_loc (EXPR_LOCATION (t), TREE_TYPE (t),
                                   CALL_EXPR_FN (t), nargs, args);
  new_call = fold (new_call);
  VERIFY_CONSTANT (new_call);
  return new_call;
}
