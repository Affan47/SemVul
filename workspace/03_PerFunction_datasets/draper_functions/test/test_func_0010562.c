expand_builtin_expect (tree arglist, rtx target)
{
  tree exp, c;
  rtx note, rtx_c;

  if (arglist == NULL_TREE
      || TREE_CHAIN (arglist) == NULL_TREE)
    return const0_rtx;
  exp = TREE_VALUE (arglist);
  c = TREE_VALUE (TREE_CHAIN (arglist));

  if (TREE_CODE (c) != INTEGER_CST)
    {
      error ("second arg to `__builtin_expect' must be a constant");
      c = integer_zero_node;
    }

  target = expand_expr (exp, target, VOIDmode, EXPAND_NORMAL);


  if (flag_guess_branch_prob && GET_CODE (target) != CONST_INT)
    {


      target = force_reg (GET_MODE (target), target);

      rtx_c = expand_expr (c, NULL_RTX, GET_MODE (target), EXPAND_NORMAL);

      note = emit_note (NOTE_INSN_EXPECTED_VALUE);
      NOTE_EXPECTED_VALUE (note) = gen_rtx_EQ (VOIDmode, target, rtx_c);
    }

  return target;
}
