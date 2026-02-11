next_runtime_abi_01_get_class_reference (tree ident)
{
  if (!flag_zero_link)
    {
      tree *chain;
      tree decl;

      for (chain = &cls_ref_chain; *chain; chain = &TREE_CHAIN (*chain))
	if (TREE_VALUE (*chain) == ident)
	  {
	    if (! TREE_PURPOSE (*chain))
	      TREE_PURPOSE (*chain) = build_class_reference_decl ();

	    return TREE_PURPOSE (*chain);
	  }

      decl = build_class_reference_decl ();
      *chain = tree_cons (decl, ident, NULL_TREE);
      return decl;
    }
  else
    {
      tree params;

      add_class_reference (ident);

      params = build_tree_list (NULL_TREE,
				my_build_string_pointer
				(IDENTIFIER_LENGTH (ident) + 1,
				 IDENTIFIER_POINTER (ident)));

      return build_function_call (input_location, objc_get_class_decl, params);
    }
}
