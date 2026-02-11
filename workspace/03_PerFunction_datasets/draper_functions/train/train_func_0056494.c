maybe_catch_exception (gimple_seq body)
{
  gimple g;
  tree decl;

  if (!flag_exceptions)
    return body;

  if (lang_hooks.eh_protect_cleanup_actions != NULL)
    decl = lang_hooks.eh_protect_cleanup_actions ();
  else
    decl = built_in_decls[BUILT_IN_TRAP];

  g = gimple_build_eh_must_not_throw (decl);
  g = gimple_build_try (body, gimple_seq_alloc_with_stmt (g),
      			GIMPLE_TRY_CATCH);

 return gimple_seq_alloc_with_stmt (g);
}
