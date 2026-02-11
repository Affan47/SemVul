cp_parser_new_expression (cp_parser* parser)
{
  bool global_scope_p;
  VEC(tree,gc) *placement;
  tree type;
  VEC(tree,gc) *initializer;
  tree nelts;
  tree ret;


  global_scope_p
    = (cp_parser_global_scope_opt (parser,
				   false)
       != NULL_TREE);

  cp_parser_require_keyword (parser, RID_NEW, RT_NEW);


  cp_parser_parse_tentatively (parser);

  placement = cp_parser_new_placement (parser);

  if (!cp_parser_parse_definitely (parser))
    {
      if (placement != NULL)
	release_tree_vector (placement);
      placement = NULL;
    }


  if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_PAREN))
    {
      cp_token *token;
      const char *saved_message = parser->type_definition_forbidden_message;


      cp_lexer_consume_token (parser->lexer);


      parser->type_definition_forbidden_message
	= G_("types may not be defined in a new-expression");
      type = cp_parser_type_id (parser);
      parser->type_definition_forbidden_message = saved_message;


      cp_parser_require (parser, CPP_CLOSE_PAREN, RT_CLOSE_PAREN);
      token = cp_lexer_peek_token (parser->lexer);


      if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_SQUARE))
	{
	  error_at (token->location,
		    "array bound forbidden after parenthesized type-id");
	  inform (token->location,
		  "try removing the parentheses around the type-id");
	  cp_parser_direct_new_declarator (parser);
	}
      nelts = NULL_TREE;
    }

  else
    type = cp_parser_new_type_id (parser, &nelts);


  if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_PAREN)
      || cp_lexer_next_token_is (parser->lexer, CPP_OPEN_BRACE))
    initializer = cp_parser_new_initializer (parser);
  else
    initializer = NULL;


  if (cp_parser_non_integral_constant_expression (parser, NIC_NEW))
    ret = error_mark_node;
  else
    {

      ret = build_new (&placement, type, nelts, &initializer, global_scope_p,
		       tf_warning_or_error);
    }

  if (placement != NULL)
    release_tree_vector (placement);
  if (initializer != NULL)
    release_tree_vector (initializer);

  return ret;
}
