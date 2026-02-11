memoize_as_thunk_prototype (const SCM expr, const SCM env SCM_UNUSED)
{
  const SCM cdr_expr = SCM_CDR (expr);
  ASSERT_SYNTAX (scm_ilength (cdr_expr) >= 0, s_bad_expression, expr);
  ASSERT_SYNTAX (scm_ilength (cdr_expr) == 1, s_expression, expr);

  SCM_SETCDR (expr, scm_cons (SCM_EOL, cdr_expr));

  return expr;
}
