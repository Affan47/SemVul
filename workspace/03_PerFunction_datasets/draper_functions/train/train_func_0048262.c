in_expr_list_p (const_rtx listp, const_rtx node)
{
  const_rtx x;

  for (x = listp; x; x = XEXP (x, 1))
    if (node == XEXP (x, 0))
      return 1;

  return 0;
}
