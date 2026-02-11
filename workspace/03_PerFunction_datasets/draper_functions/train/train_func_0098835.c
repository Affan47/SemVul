scm_m_do (SCM expr, SCM env SCM_UNUSED)
{
  SCM variables = SCM_EOL;
  SCM init_forms = SCM_EOL;
  SCM step_forms = SCM_EOL;
  SCM binding_idx;
  SCM cddr_expr;
  SCM exit_clause;
  SCM commands;
  SCM tail;

  const SCM cdr_expr = SCM_CDR (expr);
  ASSERT_SYNTAX (scm_ilength (cdr_expr) >= 0, s_bad_expression, expr);
  ASSERT_SYNTAX (scm_ilength (cdr_expr) >= 2, s_missing_expression, expr);


  binding_idx = SCM_CAR (cdr_expr);
  ASSERT_SYNTAX_2 (scm_ilength (binding_idx) >= 0,
                   s_bad_bindings, binding_idx, expr);
  for (; !scm_is_null (binding_idx); binding_idx = SCM_CDR (binding_idx))
    {
      const SCM binding = SCM_CAR (binding_idx);
      const long length = scm_ilength (binding);
      ASSERT_SYNTAX_2 (length == 2 || length == 3,
                       s_bad_binding, binding, expr);

      {
        const SCM name = SCM_CAR (binding);
        const SCM init = SCM_CADR (binding);
        const SCM step = (length == 2) ? name : SCM_CADDR (binding);
        ASSERT_SYNTAX_2 (scm_is_symbol (name), s_bad_variable, name, expr);
        ASSERT_SYNTAX_2 (scm_is_false (scm_c_memq (name, variables)),
                         s_duplicate_binding, name, expr);

        variables = scm_cons (name, variables);
        init_forms = scm_cons (init, init_forms);
        step_forms = scm_cons (step, step_forms);
      }
    }
  init_forms = scm_reverse_x (init_forms, SCM_UNDEFINED);
  step_forms = scm_reverse_x (step_forms, SCM_UNDEFINED);


  cddr_expr = SCM_CDR (cdr_expr);
  exit_clause = SCM_CAR (cddr_expr);
  ASSERT_SYNTAX_2 (scm_ilength (exit_clause) >= 1,
                   s_bad_exit_clause, exit_clause, expr);

  commands = SCM_CDR (cddr_expr);
  tail = scm_cons2 (exit_clause, commands, step_forms);
  tail = scm_cons2 (init_forms, variables, tail);
  SCM_SETCAR (expr, SCM_IM_DO);
  SCM_SETCDR (expr, tail);
  return expr;
}
