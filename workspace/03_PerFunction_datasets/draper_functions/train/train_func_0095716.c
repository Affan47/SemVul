simplify_using_condition (rtx cond, rtx *expr, regset altered)
{
  rtx rev, reve, exp = *expr;


  if (altered
      && for_each_rtx (&cond, altered_reg_used, altered))
    return;

  if (GET_CODE (cond) == EQ
      && REG_P (XEXP (cond, 0)) && CONSTANT_P (XEXP (cond, 1)))
    {
      *expr = simplify_replace_rtx (*expr, XEXP (cond, 0), XEXP (cond, 1));
      return;
    }

  if (!COMPARISON_P (exp))
    return;

  rev = reversed_condition (cond);
  reve = reversed_condition (exp);

  cond = canon_condition (cond);
  exp = canon_condition (exp);
  if (rev)
    rev = canon_condition (rev);
  if (reve)
    reve = canon_condition (reve);

  if (rtx_equal_p (exp, cond))
    {
      *expr = const_true_rtx;
      return;
    }

  if (rev && rtx_equal_p (exp, rev))
    {
      *expr = const0_rtx;
      return;
    }

  if (implies_p (cond, exp))
    {
      *expr = const_true_rtx;
      return;
    }

  if (reve && implies_p (cond, reve))
    {
      *expr = const0_rtx;
      return;
    }


  if (rev && implies_p (exp, rev))
    {
      *expr = const0_rtx;
      return;
    }


  if (rev && reve && implies_p (reve, rev))
    {
      *expr = const_true_rtx;
      return;
    }


  return;
}
