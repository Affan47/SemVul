cp_parser_type_parameter (cp_parser* parser)
{
  cp_token *token;
  tree parameter;


  token = cp_parser_require (parser, CPP_KEYWORD,
			     "`class', `typename', or `template'");
  if (!token)
    return error_mark_node;

  switch (token->keyword)
    {
    case RID_CLASS:
    case RID_TYPENAME:
      {
	tree identifier;
	tree default_argument;


	if (cp_lexer_next_token_is (parser->lexer, CPP_NAME))
	  identifier = cp_parser_identifier (parser);
	else
	  identifier = NULL_TREE;


	parameter = finish_template_type_parm (class_type_node, identifier);


	if (cp_lexer_next_token_is (parser->lexer, CPP_EQ))
	  {

	    cp_lexer_consume_token (parser->lexer);

	    default_argument = cp_parser_type_id (parser);
	  }
	else
	  default_argument = NULL_TREE;


	parameter = build_tree_list (default_argument, parameter);
      }
      break;

    case RID_TEMPLATE:
      {
	tree parameter_list;
	tree identifier;
	tree default_argument;


	cp_parser_require (parser, CPP_LESS, "`<'");

	begin_template_parm_list ();
	parameter_list
	  = cp_parser_template_parameter_list (parser);
	parameter_list = end_template_parm_list (parameter_list);

	cp_parser_require (parser, CPP_GREATER, "`>'");

	cp_parser_require_keyword (parser, RID_CLASS, "`class'");


	if (cp_lexer_next_token_is_not (parser->lexer, CPP_EQ)
	    && cp_lexer_next_token_is_not (parser->lexer, CPP_GREATER)
	    && cp_lexer_next_token_is_not (parser->lexer, CPP_COMMA))
	  {
	    identifier = cp_parser_identifier (parser);

	    if (identifier == error_mark_node)
	      identifier = NULL_TREE;
	  }
	else
	  identifier = NULL_TREE;


	parameter = finish_template_template_parm (class_type_node,
						   identifier);


	if (cp_lexer_next_token_is (parser->lexer, CPP_EQ))
	  {
	    bool is_template;


	    cp_lexer_consume_token (parser->lexer);

	    default_argument
	      = cp_parser_id_expression (parser,
					 false,
					 true,
					 &is_template,
					 false);
	    if (TREE_CODE (default_argument) == TYPE_DECL)


		 ;
	    else

	      default_argument
		= cp_parser_lookup_name (parser, default_argument,
					false,
					is_template,
					false,
					true);

	    default_argument
	      = check_template_template_default_arg (default_argument);
	  }
	else
	  default_argument = NULL_TREE;


	parameter = build_tree_list (default_argument, parameter);
      }
      break;

    default:
      abort ();
      break;
    }

  return parameter;
}
