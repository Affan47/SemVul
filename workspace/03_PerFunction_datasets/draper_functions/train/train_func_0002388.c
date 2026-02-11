expand_builtin_constant_p (exp)
     tree exp;
{
  tree arglist = TREE_OPERAND (exp, 1);
  enum machine_mode value_mode = TYPE_MODE (TREE_TYPE (exp));
  rtx tmp;

  if (arglist == 0)
    return const0_rtx;
  arglist = TREE_VALUE (arglist);


  tmp = expand_expr (arglist, NULL_RTX, VOIDmode, 0);
  tmp = gen_rtx_CONSTANT_P_RTX (value_mode, tmp);
  return tmp;
}
