cp_parser_function_definition_after_declarator (cp_parser* parser,
						bool inline_p)
{
  tree fn;
  bool ctor_initializer_p = false;
  bool saved_in_unbraced_linkage_specification_p;
  bool saved_in_function_body;
  unsigned saved_num_template_parameter_lists;
  cp_token *token;

  saved_in_function_body = parser->in_function_body;
  parser->in_function_body = true;


  token = cp_lexer_peek_token (parser->lexer);
  if (cp_lexer_next_token_is_keyword (parser->lexer, RID_RETURN))
    {

      cp_lexer_consume_token (parser->lexer);


      cp_parser_identifier (parser);

      error_at (token->location,
		"named return values are no longer supported");

      while (true)
	{
	  cp_token *token = cp_lexer_peek_token (parser->lexer);
	  if (token->type == CPP_OPEN_BRACE
	      || token->type == CPP_EOF
	      || token->type == CPP_PRAGMA_EOL)
	    break;
	  cp_lexer_consume_token (parser->lexer);
	}
    }


  saved_in_unbraced_linkage_specification_p
    = parser->in_unbraced_linkage_specification_p;
  parser->in_unbraced_linkage_specification_p = false;


  saved_num_template_parameter_lists
    = parser->num_template_parameter_lists;
  parser->num_template_parameter_lists = 0;

  start_lambda_scope (current_function_decl);


  if (cp_lexer_next_token_is_keyword (parser->lexer, RID_TRANSACTION_ATOMIC))
    ctor_initializer_p = cp_parser_function_transaction (parser,
	RID_TRANSACTION_ATOMIC);
  else if (cp_lexer_next_token_is_keyword (parser->lexer,
      RID_TRANSACTION_RELAXED))
    ctor_initializer_p = cp_parser_function_transaction (parser,
	RID_TRANSACTION_RELAXED);
  else if (cp_lexer_next_token_is_keyword (parser->lexer, RID_TRY))
    ctor_initializer_p = cp_parser_function_try_block (parser);
  else
    ctor_initializer_p
      = cp_parser_ctor_initializer_opt_and_function_body (parser);

  finish_lambda_scope ();


  fn = finish_function ((ctor_initializer_p ? 1 : 0) |
			(inline_p ? 2 : 0));

  expand_or_defer_fn (fn);

  parser->in_unbraced_linkage_specification_p
    = saved_in_unbraced_linkage_specification_p;
  parser->num_template_parameter_lists
    = saved_num_template_parameter_lists;
  parser->in_function_body = saved_in_function_body;

  return fn;
}
