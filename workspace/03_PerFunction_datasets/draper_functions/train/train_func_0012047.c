expand_builtin_mathfn_ternary (tree exp, rtx target, rtx subtarget)
{
  optab builtin_optab;
  rtx op0, op1, op2, insns;
  tree fndecl = get_callee_fndecl (exp);
  tree arg0, arg1, arg2;
  enum machine_mode mode;

  if (!validate_arglist (exp, REAL_TYPE, REAL_TYPE, REAL_TYPE, VOID_TYPE))
    return NULL_RTX;

  arg0 = CALL_EXPR_ARG (exp, 0);
  arg1 = CALL_EXPR_ARG (exp, 1);
  arg2 = CALL_EXPR_ARG (exp, 2);

  switch (DECL_FUNCTION_CODE (fndecl))
    {
    CASE_FLT_FN (BUILT_IN_FMA):
      builtin_optab = fma_optab; break;
    default:
      gcc_unreachable ();
    }


  mode = TYPE_MODE (TREE_TYPE (exp));


  if (optab_handler (builtin_optab, mode) == CODE_FOR_nothing)
    return NULL_RTX;

  target = gen_reg_rtx (mode);


  CALL_EXPR_ARG (exp, 0) = arg0 = builtin_save_expr (arg0);
  CALL_EXPR_ARG (exp, 1) = arg1 = builtin_save_expr (arg1);
  CALL_EXPR_ARG (exp, 2) = arg2 = builtin_save_expr (arg2);

  op0 = expand_expr (arg0, subtarget, VOIDmode, EXPAND_NORMAL);
  op1 = expand_normal (arg1);
  op2 = expand_normal (arg2);

  start_sequence ();


  target = expand_ternary_op (mode, builtin_optab, op0, op1, op2,
			      target, 0);


  if (target == 0)
    {
      end_sequence ();
      return expand_call (exp, target, target == const0_rtx);
    }


  insns = get_insns ();
  end_sequence ();
  emit_insn (insns);

  return target;
}
