cp_parser_objc_method_keyword_params (cp_parser* parser, tree* attributes)
{
  tree params = NULL_TREE;
  bool maybe_unary_selector_p = true;
  cp_token *token = cp_lexer_peek_token (parser->lexer);

  while (cp_parser_objc_selector_p (token->type) || token->type == CPP_COLON)
    {
      tree selector = NULL_TREE, type_name, identifier;
      tree parm_attr = NULL_TREE;

      if (token->keyword == RID_ATTRIBUTE)
	break;

      if (token->type != CPP_COLON)
	selector = cp_parser_objc_selector (parser);


      if (maybe_unary_selector_p
	  && cp_lexer_next_token_is_not (parser->lexer, CPP_COLON))
	{
	  params = selector;
	  break;
	}

      maybe_unary_selector_p = false;
      if (!cp_parser_require (parser, CPP_COLON, RT_COLON))
	{


	  break;
	}
      type_name = cp_parser_objc_typename (parser);

      if (cp_lexer_next_token_is_keyword (parser->lexer, RID_ATTRIBUTE))
	parm_attr = cp_parser_attributes_opt (parser);
      identifier = cp_parser_identifier (parser);

      params
	= chainon (params,
		   objc_build_keyword_decl (selector,
					    type_name,
					    identifier,
					    parm_attr));

      token = cp_lexer_peek_token (parser->lexer);
    }

  if (params == NULL_TREE)
    {
      cp_parser_error (parser, "objective-c++ method declaration is expected");
      return error_mark_node;
    }


  if (token->keyword == RID_ATTRIBUTE)
    {
      *attributes = cp_parser_attributes_opt (parser);
      if (cp_lexer_next_token_is (parser->lexer, CPP_SEMICOLON)
	  || cp_lexer_next_token_is (parser->lexer, CPP_OPEN_BRACE))
	return params;
      cp_parser_error (parser,
		       "method attributes must be specified at the end");
      return error_mark_node;
    }

  if (params == NULL_TREE)
    {
      cp_parser_error (parser, "objective-c++ method declaration is expected");
      return error_mark_node;
    }
  return params;
}
