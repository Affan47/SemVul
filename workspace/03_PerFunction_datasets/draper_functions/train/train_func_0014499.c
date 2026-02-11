finish_try_stmt (struct objc_try_context **cur_try_context)
{
  tree stmt;
  struct objc_try_context *c = *cur_try_context;

  if (flag_objc_sjlj_exceptions)
    {
      bool save = in_late_binary_op;
      in_late_binary_op = true;
      if (!c->finally_body)
	{
	  c->finally_locus = input_location;
	  c->end_finally_locus = input_location;
	}
      stmt = next_sjlj_build_try_catch_finally (cur_try_context);
      in_late_binary_op = save;
    }
  else

    {

      stmt = c->try_body;
      if (c->catch_list)
	stmt = build_stmt (c->try_locus, TRY_CATCH_EXPR, stmt, c->catch_list);
      if (c->finally_body)
	stmt = build_stmt (c->try_locus, TRY_FINALLY_EXPR, stmt, c->finally_body);
    }
  return stmt;
}
