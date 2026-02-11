same_signature_p (const_tree fndecl, const_tree base_fndecl)
{


  if (DECL_DESTRUCTOR_P (base_fndecl) && DECL_DESTRUCTOR_P (fndecl)
      && special_function_p (base_fndecl) == special_function_p (fndecl))
    return 1;


  if (DECL_DESTRUCTOR_P (base_fndecl) || DECL_DESTRUCTOR_P (fndecl))
    return 0;

  if (DECL_NAME (fndecl) == DECL_NAME (base_fndecl)
      || (DECL_CONV_FN_P (fndecl)
	  && DECL_CONV_FN_P (base_fndecl)
	  && same_type_p (DECL_CONV_FN_TYPE (fndecl),
			  DECL_CONV_FN_TYPE (base_fndecl))))
    {
      tree types, base_types;
      types = TYPE_ARG_TYPES (TREE_TYPE (fndecl));
      base_types = TYPE_ARG_TYPES (TREE_TYPE (base_fndecl));
      if ((cp_type_quals (TREE_TYPE (TREE_VALUE (base_types)))
	   == cp_type_quals (TREE_TYPE (TREE_VALUE (types))))
	  && compparms (TREE_CHAIN (base_types), TREE_CHAIN (types)))
	return 1;
    }
  return 0;
}
