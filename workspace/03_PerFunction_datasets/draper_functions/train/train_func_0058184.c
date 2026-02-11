unmemoize_expression (const SCM expr, const SCM env)
{
  if (SCM_ILOCP (expr))
    {
      SCM frame_idx;
      unsigned long int frame_nr;
      SCM symbol_idx;
      unsigned long int symbol_nr;

      for (frame_idx = env, frame_nr = SCM_IFRAME (expr);
           frame_nr != 0;
           frame_idx = SCM_CDR (frame_idx), --frame_nr)
        ;
      for (symbol_idx = SCM_CAAR (frame_idx), symbol_nr = SCM_IDIST (expr);
           symbol_nr != 0;
           symbol_idx = SCM_CDR (symbol_idx), --symbol_nr)
        ;
      return SCM_ICDRP (expr) ? symbol_idx : SCM_CAR (symbol_idx);
    }
  else if (SCM_VARIABLEP (expr))
    {
      const SCM sym = scm_module_reverse_lookup (scm_env_module (env), expr);
      return scm_is_true (sym) ? sym : sym_three_question_marks;
    }
  else if (scm_is_simple_vector (expr))
    {
      return scm_list_2 (scm_sym_quote, expr);
    }
  else if (!scm_is_pair (expr))
    {
      return expr;
    }
  else if (SCM_ISYMP (SCM_CAR (expr)))
    {
      return unmemoize_builtin_macro (expr, env);
    }
  else
    {
      return unmemoize_exprs (expr, env);
    }
}
