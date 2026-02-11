cp_parser_set_decl_spec_type (cp_decl_specifier_seq *decl_specs,
			      tree type_spec,
			      cp_token *token,
			      bool type_definition_p)
{
  decl_specs->any_specifiers_p = true;


  if (decl_spec_seq_has_spec_p (decl_specs, ds_typedef)
      && !type_definition_p
      && (type_spec == boolean_type_node
	  || type_spec == char16_type_node
	  || type_spec == char32_type_node
	  || type_spec == wchar_type_node)
      && (decl_specs->type
	  || decl_spec_seq_has_spec_p (decl_specs, ds_long)
	  || decl_spec_seq_has_spec_p (decl_specs, ds_short)
	  || decl_spec_seq_has_spec_p (decl_specs, ds_unsigned)
	  || decl_spec_seq_has_spec_p (decl_specs, ds_signed)))
    {
      decl_specs->redefined_builtin_type = type_spec;
      set_and_check_decl_spec_loc (decl_specs,
				   ds_redefined_builtin_type_spec,
				   token);
      if (!decl_specs->type)
	{
	  decl_specs->type = type_spec;
	  decl_specs->type_definition_p = false;
	  set_and_check_decl_spec_loc (decl_specs,ds_type_spec, token);
	}
    }
  else if (decl_specs->type)
    decl_specs->multiple_types_p = true;
  else
    {
      decl_specs->type = type_spec;
      decl_specs->type_definition_p = type_definition_p;
      decl_specs->redefined_builtin_type = NULL_TREE;
      set_and_check_decl_spec_loc (decl_specs, ds_type_spec, token);
    }
}
