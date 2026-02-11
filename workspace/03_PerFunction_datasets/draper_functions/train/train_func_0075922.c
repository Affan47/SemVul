check_bindings (const SCM bindings, const SCM expr)
{
  SCM binding_idx;

  ASSERT_SYNTAX_2 (scm_ilength (bindings) >= 0,
                   s_bad_bindings, bindings, expr);

  binding_idx = bindings;
  for (; !scm_is_null (binding_idx); binding_idx = SCM_CDR (binding_idx))
    {
      SCM name;

      const SCM binding = SCM_CAR (binding_idx);
      ASSERT_SYNTAX_2 (scm_ilength (binding) == 2,
                       s_bad_binding, binding, expr);

      name = SCM_CAR (binding);
      ASSERT_SYNTAX_2 (scm_is_symbol (name), s_bad_variable, name, expr);
    }
}
