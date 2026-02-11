cp_parser_direct_new_declarator (cp_parser* parser)
{
  cp_declarator *declarator = NULL;

  while (true)
    {
      tree expression;


      cp_parser_require (parser, CPP_OPEN_SQUARE, RT_OPEN_SQUARE);

      if (!declarator)
	{
	  cp_token *token = cp_lexer_peek_token (parser->lexer);
	  expression = cp_parser_expression (parser, false, NULL);


	  if (!processing_template_decl)
	    {
	      expression
		= build_expr_type_conversion (WANT_INT | WANT_ENUM,
					      expression,
					      true);
	      if (!expression)
		{
		  error_at (token->location,
			    "expression in new-declarator must have integral "
			    "or enumeration type");
		  expression = error_mark_node;
		}
	    }
	}

      else
	expression
	  = cp_parser_constant_expression (parser,
					   false,
					   NULL);

      cp_parser_require (parser, CPP_CLOSE_SQUARE, RT_CLOSE_SQUARE);


      declarator = make_array_declarator (declarator, expression);


      if (cp_lexer_next_token_is_not (parser->lexer, CPP_OPEN_SQUARE))
	break;
    }

  return declarator;
}
