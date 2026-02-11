expand_builtin_fabs (tree arglist, rtx target, rtx subtarget)
{
  enum machine_mode mode;
  tree arg;
  rtx op0;

  if (!validate_arglist (arglist, REAL_TYPE, VOID_TYPE))
    return 0;

  arg = TREE_VALUE (arglist);
  mode = TYPE_MODE (TREE_TYPE (arg));
  op0 = expand_expr (arg, subtarget, VOIDmode, 0);
  return expand_abs (mode, op0, target, 0, safe_from_p (target, arg, 1));
}
