finish_catch (struct objc_try_context **cur_try_context, tree curr_catch)
{
  struct objc_try_context *ct;
  tree try_exp, func, *l, t ;
  location_t loc = (*cur_try_context)->try_locus;

  if (!curr_catch || curr_catch == error_mark_node)
    return;

  t = CATCH_BODY (curr_catch);
  if (TREE_CODE (t) == BIND_EXPR)
    {

      objc_begin_try_stmt (loc, BIND_EXPR_BODY (t));
      BIND_EXPR_BODY (t) = NULL_TREE;
      l = &BIND_EXPR_BODY (t);
    }
  else
    {

      objc_begin_try_stmt (loc, t);
      CATCH_BODY (curr_catch) = NULL_TREE;
      l = &CATCH_BODY (curr_catch);
    }


  ct = *cur_try_context;
  func = build_function_call_vec (loc, objc2_end_catch_decl, NULL, NULL);
  append_to_statement_list (func, &ct->finally_body);
  try_exp = build_stmt (loc, TRY_FINALLY_EXPR, ct->try_body, ct->finally_body);
  *cur_try_context = ct->outer;
  free (ct);
  append_to_statement_list (try_exp, l);
  append_to_statement_list (curr_catch, &((*cur_try_context)->catch_list));
}
