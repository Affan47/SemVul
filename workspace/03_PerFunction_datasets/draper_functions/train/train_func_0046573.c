cp_make_fname_decl (location_t loc, tree id, int type_dep)
{
  const char *const name = (type_dep && processing_template_decl
			    ? NULL : fname_as_string (type_dep));
  tree type;
  tree init = cp_fname_init (name, &type);
  tree decl = build_decl (loc, VAR_DECL, id, type);

  if (name)
    free (CONST_CAST (char *, name));


  DECL_CONTEXT (decl) = current_function_decl;
  DECL_PRETTY_FUNCTION_P (decl) = type_dep;

  TREE_STATIC (decl) = 1;
  TREE_READONLY (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;

  TREE_USED (decl) = 1;

  if (current_function_decl)
    {
      cp_binding_level *b = current_binding_level;
      if (b->kind == sk_function_parms)
	return error_mark_node;
      while (b->level_chain->kind != sk_function_parms)
	b = b->level_chain;
      pushdecl_with_scope (decl, b, false);
      cp_finish_decl (decl, init, false, NULL_TREE,
		      LOOKUP_ONLYCONVERTING);
    }
  else
    {
      DECL_THIS_STATIC (decl) = true;
      pushdecl_top_level_and_finish (decl, init);
    }

  return decl;
}
