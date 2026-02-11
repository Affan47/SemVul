ipa_get_jf_pass_through_result (struct ipa_jump_func *jfunc, tree input)
{
  tree restype, res;

  gcc_checking_assert (is_gimple_ip_invariant (input));
  if (jfunc->value.pass_through.operation == NOP_EXPR)
    return input;

  if (TREE_CODE_CLASS (jfunc->value.pass_through.operation)
      == tcc_comparison)
    restype = boolean_type_node;
  else
    restype = TREE_TYPE (input);
  res = fold_binary (jfunc->value.pass_through.operation, restype,
		     input, jfunc->value.pass_through.operand);

  if (res && !is_gimple_ip_invariant (res))
    return NULL_TREE;

  return res;
}
