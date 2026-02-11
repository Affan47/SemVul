begin_scope (scope_kind kind, tree entity)
{
  cp_binding_level *scope;


  if (!ENABLE_SCOPE_CHECKING && free_binding_level)
    {
      scope = free_binding_level;
      memset (scope, 0, sizeof (cp_binding_level));
      free_binding_level = scope->level_chain;
    }
  else
    scope = ggc_alloc_cleared_cp_binding_level ();

  scope->this_entity = entity;
  scope->more_cleanups_ok = true;
  switch (kind)
    {
    case sk_cleanup:
      scope->keep = true;
      break;

    case sk_template_spec:
      scope->explicit_spec_p = true;
      kind = sk_template_parms;

    case sk_template_parms:
    case sk_block:
    case sk_try:
    case sk_catch:
    case sk_for:
    case sk_cond:
    case sk_class:
    case sk_scoped_enum:
    case sk_function_parms:
    case sk_omp:
      scope->keep = keep_next_level_flag;
      break;

    case sk_namespace:
      NAMESPACE_LEVEL (entity) = scope;
      scope->static_decls =
	VEC_alloc (tree, gc,
		   DECL_NAME (entity) == std_identifier
		   || DECL_NAME (entity) == global_scope_name
		   ? 200 : 10);
      break;

    default:

      gcc_unreachable ();
      break;
    }
  scope->kind = kind;

  push_binding_level (scope);

  return scope;
}
