cp_parser_alias_declaration (cp_parser* parser)
{
  tree id, type, decl, pushed_scope = NULL_TREE, attributes;
  location_t id_location;
  cp_declarator *declarator;
  cp_decl_specifier_seq decl_specs;
  bool member_p;
  const char *saved_message = NULL;


  cp_parser_require_keyword (parser, RID_USING, RT_USING);
  id_location = cp_lexer_peek_token (parser->lexer)->location;
  id = cp_parser_identifier (parser);
  if (id == error_mark_node)
    return error_mark_node;

  attributes = cp_parser_attributes_opt (parser);
  if (attributes == error_mark_node)
    return error_mark_node;

  cp_parser_require (parser, CPP_EQ, RT_EQ);

  if (cp_parser_error_occurred (parser))
    return error_mark_node;


  if (parser->num_template_parameter_lists)
    {
      saved_message = parser->type_definition_forbidden_message;
      parser->type_definition_forbidden_message =
	G_("types may not be defined in alias template declarations");
    }

  type = cp_parser_type_id (parser);


  if (parser->num_template_parameter_lists)
    parser->type_definition_forbidden_message = saved_message;

  cp_parser_require (parser, CPP_SEMICOLON, RT_SEMICOLON);

  if (cp_parser_error_occurred (parser))
    return error_mark_node;


  clear_decl_specs (&decl_specs);
  decl_specs.type = type;
  decl_specs.attributes = attributes;
  ++decl_specs.specs[(int) ds_typedef];
  ++decl_specs.specs[(int) ds_alias];

  declarator = make_id_declarator (NULL_TREE, id, sfk_none);
  declarator->id_loc = id_location;

  member_p = at_class_scope_p ();
  if (member_p)
    decl = grokfield (declarator, &decl_specs, NULL_TREE, false,
		      NULL_TREE, attributes);
  else
    decl = start_decl (declarator, &decl_specs, 0,
		       attributes, NULL_TREE, &pushed_scope);
  if (decl == error_mark_node)
    return decl;

  cp_finish_decl (decl, NULL_TREE, 0, NULL_TREE, 0);

  if (pushed_scope)
    pop_scope (pushed_scope);


  if (DECL_LANG_SPECIFIC (decl)
      && DECL_TEMPLATE_INFO (decl)
      && PRIMARY_TEMPLATE_P (DECL_TI_TEMPLATE (decl)))
    {
      decl = DECL_TI_TEMPLATE (decl);
      if (member_p)
	check_member_template (decl);
    }

  return decl;
}
