canonicalize_define (const SCM expr)
{
  SCM body;
  SCM variable;

  const SCM cdr_expr = SCM_CDR (expr);
  ASSERT_SYNTAX (scm_ilength (cdr_expr) >= 0, s_bad_expression, expr);
  ASSERT_SYNTAX (scm_ilength (cdr_expr) >= 2, s_missing_expression, expr);

  body = SCM_CDR (cdr_expr);
  variable = SCM_CAR (cdr_expr);
  while (scm_is_pair (variable))
    {


      const SCM formals = SCM_CDR (variable);
      const SCM tail = scm_cons (formals, body);


      const SCM lambda = scm_cons_source (variable, scm_sym_lambda, tail);

      body = scm_list_1 (lambda);
      variable = SCM_CAR (variable);
    }
  ASSERT_SYNTAX_2 (scm_is_symbol (variable), s_bad_variable, variable, expr);
  ASSERT_SYNTAX (scm_ilength (body) == 1, s_expression, expr);

  SCM_SETCAR (cdr_expr, variable);
  SCM_SETCDR (cdr_expr, body);
  return expr;
}
