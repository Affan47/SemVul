replace_in_expr (rtx *expr, rtx dest, rtx src)
{
  rtx old = *expr;
  *expr = simplify_replace_rtx (*expr, dest, src);
  if (old == *expr)
    return;
  while (for_each_rtx (expr, replace_single_def_regs, expr) != 0)
    continue;
}
