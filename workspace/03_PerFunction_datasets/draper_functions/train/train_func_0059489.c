scm_m_quote (SCM expr, SCM env SCM_UNUSED)
{
  SCM quotee;

  const SCM cdr_expr = SCM_CDR (expr);
  ASSERT_SYNTAX (scm_ilength (cdr_expr) >= 0, s_bad_expression, expr);
  ASSERT_SYNTAX (scm_ilength (cdr_expr) == 1, s_expression, expr);
  quotee = SCM_CAR (cdr_expr);
  if (is_self_quoting_p (quotee))
    return quotee;

  SCM_SETCAR (expr, SCM_IM_QUOTE);
  SCM_SETCDR (expr, quotee);
  return expr;
}
