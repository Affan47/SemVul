cp_parser_mem_initializer_id (cp_parser* parser)
{
  bool global_scope_p;
  bool nested_name_specifier_p;
  bool template_p = false;
  tree id;


  if (cp_lexer_next_token_is_keyword (parser->lexer, RID_TYPENAME))
    {
      error ("keyword `typename' not allowed in this context (a qualified "
	     "member initializer is implicitly a type)");
      cp_lexer_consume_token (parser->lexer);
    }

  global_scope_p
    = (cp_parser_global_scope_opt (parser,
				   false)
       != NULL_TREE);


  nested_name_specifier_p
    = (cp_parser_nested_name_specifier_opt (parser,
					    true,
					    true,
					    true,
					    true)
       != NULL_TREE);
  if (nested_name_specifier_p)
    template_p = cp_parser_optional_template_keyword (parser);


  if (global_scope_p || nested_name_specifier_p)
    return cp_parser_class_name (parser,
				 true,
				 template_p,
				 false,
				 true,
				 false,
				 true);

  cp_parser_parse_tentatively (parser);

  id = cp_parser_class_name (parser,
			     true,
			     false,
			     false,
			     true,
			     false,
			     true);

  if (cp_parser_parse_definitely (parser))
    return id;

  return cp_parser_identifier (parser);
}
