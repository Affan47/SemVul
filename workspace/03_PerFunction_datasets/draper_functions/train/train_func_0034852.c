do_pushlevel (scope_kind sk)
{
  if (stmts_are_full_exprs_p ())
    {
      if (!processing_template_decl)
	add_scope_stmt (1, 0);
      begin_scope (sk, NULL);
    }
}
