cp_parser_namespace_definition (cp_parser* parser)
{
  tree identifier, attribs;
  bool has_visibility;
  bool is_inline;

  if (cp_lexer_next_token_is_keyword (parser->lexer, RID_INLINE))
    {
      maybe_warn_cpp0x (CPP0X_INLINE_NAMESPACES);
      is_inline = true;
      cp_lexer_consume_token (parser->lexer);
    }
  else
    is_inline = false;


  cp_parser_require_keyword (parser, RID_NAMESPACE, RT_NAMESPACE);


  if (cp_lexer_next_token_is (parser->lexer, CPP_NAME))
    identifier = cp_parser_identifier (parser);
  else
    identifier = NULL_TREE;


  attribs = cp_parser_attributes_opt (parser);


  cp_parser_require (parser, CPP_OPEN_BRACE, RT_OPEN_BRACE);

  push_namespace (identifier);


  if (is_inline)
    {
      tree name_space = current_namespace;

      DECL_NAMESPACE_ASSOCIATIONS (name_space)
	= tree_cons (CP_DECL_CONTEXT (name_space), NULL_TREE,
		     DECL_NAMESPACE_ASSOCIATIONS (name_space));

      pop_namespace ();
      do_using_directive (name_space);
      push_namespace (identifier);
    }

  has_visibility = handle_namespace_attrs (current_namespace, attribs);


  cp_parser_namespace_body (parser);

  if (has_visibility)
    pop_visibility (1);


  pop_namespace ();

  cp_parser_require (parser, CPP_CLOSE_BRACE, RT_CLOSE_BRACE);
}
