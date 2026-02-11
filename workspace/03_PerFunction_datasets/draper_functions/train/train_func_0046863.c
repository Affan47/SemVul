cp_parser_mem_initializer (cp_parser* parser)
{
  tree mem_initializer_id;
  tree expression_list;
  tree member;
  cp_token *token = cp_lexer_peek_token (parser->lexer);


  if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_PAREN))
    {
      permerror (token->location,
		 "anachronistic old-style base class initializer");
      mem_initializer_id = NULL_TREE;
    }
  else
    {
      mem_initializer_id = cp_parser_mem_initializer_id (parser);
      if (mem_initializer_id == error_mark_node)
	return mem_initializer_id;
    }
  member = expand_member_init (mem_initializer_id);
  if (member && !DECL_P (member))
    in_base_initializer = 1;

  if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_BRACE))
    {
      bool expr_non_constant_p;
      maybe_warn_cpp0x (CPP0X_INITIALIZER_LISTS);
      expression_list = cp_parser_braced_list (parser, &expr_non_constant_p);
      CONSTRUCTOR_IS_DIRECT_INIT (expression_list) = 1;
      expression_list = build_tree_list (NULL_TREE, expression_list);
    }
  else
    {
      vec<tree, va_gc> *vec;
      vec = cp_parser_parenthesized_expression_list (parser, non_attr,
						     false,
						     true,
						     NULL);
      if (vec == NULL)
	return error_mark_node;
      expression_list = build_tree_list_vec (vec);
      release_tree_vector (vec);
    }

  if (expression_list == error_mark_node)
    return error_mark_node;
  if (!expression_list)
    expression_list = void_type_node;

  in_base_initializer = 0;

  return member ? build_tree_list (member, expression_list) : error_mark_node;
}
