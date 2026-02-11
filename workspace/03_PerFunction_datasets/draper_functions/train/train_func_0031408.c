scm_m_begin (SCM expr, SCM env SCM_UNUSED)
{
  const SCM cdr_expr = SCM_CDR (expr);


  ASSERT_SYNTAX (scm_ilength (cdr_expr) >= 0, s_bad_expression, expr);

  SCM_SETCAR (expr, SCM_IM_BEGIN);
  return expr;
}
