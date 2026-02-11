cp_parser_explicit_instantiation (cp_parser* parser)
{
  int declares_class_or_enum;
  cp_decl_specifier_seq decl_specifiers;
  tree extension_specifier = NULL_TREE;

  timevar_push (TV_TEMPLATE_INST);


  if (cp_parser_allow_gnu_extensions_p (parser))
    {
      extension_specifier
	= cp_parser_storage_class_specifier_opt (parser);
      if (!extension_specifier)
	extension_specifier
	  = cp_parser_function_specifier_opt (parser,
					      NULL);
    }


  cp_parser_require_keyword (parser, RID_TEMPLATE, RT_TEMPLATE);


  begin_explicit_instantiation ();


  push_deferring_access_checks (dk_no_check);

  cp_parser_decl_specifier_seq (parser,
				CP_PARSER_FLAGS_OPTIONAL,
				&decl_specifiers,
				&declares_class_or_enum);


  if (declares_class_or_enum && cp_parser_declares_only_class_p (parser))
    {
      tree type;

      type = check_tag_decl (&decl_specifiers);


      pop_deferring_access_checks ();
      if (type)
	do_type_instantiation (type, extension_specifier,
			       tf_error);
    }
  else
    {
      cp_declarator *declarator;
      tree decl;


      declarator
	= cp_parser_declarator (parser, CP_PARSER_DECLARATOR_NAMED,
				NULL,
				NULL,
				false);
      if (declares_class_or_enum & 2)
	cp_parser_check_for_definition_in_return_type (declarator,
						       decl_specifiers.type,
						       decl_specifiers.type_location);
      if (declarator != cp_error_declarator)
	{
	  if (decl_specifiers.specs[(int)ds_inline])
	    permerror (input_location, "explicit instantiation shall not use"
		       " %<inline%> specifier");
	  if (decl_specifiers.specs[(int)ds_constexpr])
	    permerror (input_location, "explicit instantiation shall not use"
		       " %<constexpr%> specifier");

	  decl = grokdeclarator (declarator, &decl_specifiers,
				 NORMAL, 0, &decl_specifiers.attributes);


	  pop_deferring_access_checks ();

	  do_decl_instantiation (decl, extension_specifier);
	}
      else
	{
	  pop_deferring_access_checks ();

	  cp_parser_skip_to_end_of_statement (parser);
	}
    }

  end_explicit_instantiation ();

  cp_parser_consume_semicolon_at_end_of_statement (parser);

  timevar_pop (TV_TEMPLATE_INST);
}
