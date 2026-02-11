c_parser_parms_list_declarator (c_parser *parser, tree attrs, tree expr)
{
  bool bad_parm = false;


  if (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      struct c_arg_info *ret = build_arg_info ();
      c_parser_consume_token (parser);
      return ret;
    }
  if (c_parser_next_token_is (parser, CPP_ELLIPSIS))
    {
      struct c_arg_info *ret = build_arg_info ();

      if (flag_allow_parameterless_variadic_functions)
        {

          ret->types = NULL_TREE;
        }
      else
        {

          ret->types = error_mark_node;
          error_at (c_parser_peek_token (parser)->location,
                    "ISO C requires a named argument before %<...%>");
        }
      c_parser_consume_token (parser);
      if (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  return ret;
	}
      else
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  return NULL;
	}
    }


  while (true)
    {

      struct c_parm *parm = c_parser_parameter_declaration (parser, attrs);
      attrs = NULL_TREE;
      if (parm == NULL)
	bad_parm = true;
      else
	push_parm_decl (parm, &expr);
      if (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  tree new_attrs;
	  c_parser_consume_token (parser);
	  mark_forward_parm_decls ();
	  new_attrs = c_parser_attributes (parser);
	  return c_parser_parms_list_declarator (parser, new_attrs, expr);
	}
      if (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  if (bad_parm)
	    return NULL;
	  else
	    return get_parm_info (false, expr);
	}
      if (!c_parser_require (parser, CPP_COMMA,
			     "expected %<;%>, %<,%> or %<)%>"))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, NULL);
	  return NULL;
	}
      if (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  if (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_consume_token (parser);
	      if (bad_parm)
		return NULL;
	      else
		return get_parm_info (true, expr);
	    }
	  else
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      return NULL;
	    }
	}
    }
}
