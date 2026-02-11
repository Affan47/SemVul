cp_parser_postfix_open_square_expression (cp_parser *parser,
					  tree postfix_expression,
					  bool for_offsetof)
{
  tree index;


  cp_lexer_consume_token (parser->lexer);


  if (for_offsetof)
    index = cp_parser_constant_expression (parser, false, NULL);
  else
    {
      if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_BRACE))
	{
	  bool expr_nonconst_p;
	  maybe_warn_cpp0x (CPP0X_INITIALIZER_LISTS);
	  index = cp_parser_braced_list (parser, &expr_nonconst_p);
	}
      else
	index = cp_parser_expression (parser, false, NULL);
    }


  cp_parser_require (parser, CPP_CLOSE_SQUARE, RT_CLOSE_SQUARE);


  postfix_expression = grok_array_decl (postfix_expression, index);


  if (!for_offsetof
      && (cp_parser_non_integral_constant_expression (parser, NIC_ARRAY_REF)))
    postfix_expression = error_mark_node;

  return postfix_expression;
}
