implicitly_declare (tree functionid)
{
  tree decl = any_external_decl (functionid);

  if (decl)
    {


      if (!C_DECL_IMPLICIT (decl))
	{
	  implicit_decl_warning (DECL_NAME (decl));
	  if (! DECL_FILE_SCOPE_P (decl))
	    warning ("%Jprevious declaration of '%D'", decl, decl);
	  C_DECL_IMPLICIT (decl) = 1;
	}


      if (current_scope == global_scope)
	return decl;


      return pushdecl (copy_node (decl));
    }


  decl = build_decl (FUNCTION_DECL, functionid, default_function_type);
  DECL_EXTERNAL (decl) = 1;
  TREE_PUBLIC (decl) = 1;
  C_DECL_IMPLICIT (decl) = 1;
  implicit_decl_warning (functionid);


  decl = pushdecl (decl);


  rest_of_decl_compilation (decl, NULL, 0, 0);


  gen_aux_info_record (decl, 0, 1, 0);


  decl_attributes (&decl, NULL_TREE, 0);

  return decl;
}
