m_expand_body (const SCM forms, const SCM env)
{


  SCM cdr_forms = SCM_CDR (forms);
  SCM form_idx = cdr_forms;
  SCM definitions = SCM_EOL;
  SCM sequence = SCM_EOL;


  while (!scm_is_null (form_idx))
    {
      const SCM form = SCM_CAR (form_idx);
      const SCM new_form = expand_user_macros (form, env);
      if (is_system_macro_p (scm_sym_define, new_form, env))
	{
	  definitions = scm_cons (new_form, definitions);
	  form_idx = SCM_CDR (form_idx);
	}
      else if (is_system_macro_p (scm_sym_begin, new_form, env))
	{


          const SCM grouped_forms = SCM_CDR (new_form);
          unsigned int found_definition = 0;
          unsigned int found_expression = 0;
          SCM grouped_form_idx = grouped_forms;
          while (!found_expression && !scm_is_null (grouped_form_idx))
            {
              const SCM inner_form = SCM_CAR (grouped_form_idx);
              const SCM new_inner_form = expand_user_macros (inner_form, env);
              if (is_system_macro_p (scm_sym_define, new_inner_form, env))
                {
                  found_definition = 1;
                  definitions = scm_cons (new_inner_form, definitions);
                  grouped_form_idx = SCM_CDR (grouped_form_idx);
                }
              else if (is_system_macro_p (scm_sym_begin, new_inner_form, env))
                {
                  const SCM inner_group = SCM_CDR (new_inner_form);
                  grouped_form_idx
                    = scm_append (scm_list_2 (inner_group,
                                              SCM_CDR (grouped_form_idx)));
                }
              else
                {


                  ASSERT_SYNTAX (!found_definition, s_mixed_body_forms, form);
                  found_expression = 1;
                  grouped_form_idx = SCM_EOL;
                }
            }


          if (!found_expression)
            {
              form_idx = SCM_CDR (form_idx);
            }
          else
            {
              sequence = form_idx;
              form_idx = SCM_EOL;
            }
	}
      else
	{


          sequence = form_idx;
          form_idx = SCM_EOL;
	}
    }


  ASSERT_SYNTAX (scm_is_pair (sequence), s_missing_body_expression, cdr_forms);

  if (!scm_is_null (definitions))
    {
      SCM definition_idx;
      SCM letrec_tail;
      SCM letrec_expression;
      SCM new_letrec_expression;

      SCM bindings = SCM_EOL;
      for (definition_idx = definitions;
           !scm_is_null (definition_idx);
           definition_idx = SCM_CDR (definition_idx))
	{
	  const SCM definition = SCM_CAR (definition_idx);
	  const SCM canonical_definition = canonicalize_define (definition);
	  const SCM binding = SCM_CDR (canonical_definition);
	  bindings = scm_cons (binding, bindings);
	};

      letrec_tail = scm_cons (bindings, sequence);

      letrec_expression = scm_cons_source (forms, scm_sym_letrec, letrec_tail);
      new_letrec_expression = scm_m_letrec (letrec_expression, env);
      SCM_SETCAR (forms, new_letrec_expression);
      SCM_SETCDR (forms, SCM_EOL);
    }
  else
    {
      SCM_SETCAR (forms, SCM_CAR (sequence));
      SCM_SETCDR (forms, SCM_CDR (sequence));
    }
}
