cp_parser_ctor_initializer_opt_and_function_body (cp_parser *parser,
						  bool in_function_try_block)
{
  tree body, list;
  bool ctor_initializer_p;
  const bool check_body_p =
     DECL_CONSTRUCTOR_P (current_function_decl)
     && DECL_DECLARED_CONSTEXPR_P (current_function_decl);
  tree last = NULL;


  body = begin_function_body ();

  ctor_initializer_p = cp_parser_ctor_initializer_opt (parser);


  if (check_body_p)
    {
      list = cur_stmt_list;
      if (STATEMENT_LIST_TAIL (list))
	last = STATEMENT_LIST_TAIL (list)->stmt;
    }

  cp_parser_function_body (parser, in_function_try_block);
  if (check_body_p)
    check_constexpr_ctor_body (last, list);

  finish_function_body (body);

  return ctor_initializer_p;
}
