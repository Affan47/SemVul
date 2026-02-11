build_anon_union_vars (tree type, tree object)
{
  tree main_decl = NULL_TREE;
  tree field;


  if (TREE_CODE (type) != UNION_TYPE)
    {
      error ("anonymous struct not inside named type");
      return error_mark_node;
    }

  for (field = TYPE_FIELDS (type);
       field != NULL_TREE;
       field = DECL_CHAIN (field))
    {
      tree decl;
      tree ref;

      if (DECL_ARTIFICIAL (field))
	continue;
      if (TREE_CODE (field) != FIELD_DECL)
	{
	  permerror (input_location, "%q+#D invalid; an anonymous union can only "
		     "have non-static data members", field);
	  continue;
	}

      if (TREE_PRIVATE (field))
	permerror (input_location, "private member %q+#D in anonymous union", field);
      else if (TREE_PROTECTED (field))
	permerror (input_location, "protected member %q+#D in anonymous union", field);

      if (processing_template_decl)
	ref = build_min_nt_loc (UNKNOWN_LOCATION, COMPONENT_REF, object,
				DECL_NAME (field), NULL_TREE);
      else
	ref = build_class_member_access_expr (object, field, NULL_TREE,
					      false, tf_warning_or_error);

      if (DECL_NAME (field))
	{
	  tree base;

	  decl = build_decl (input_location,
			     VAR_DECL, DECL_NAME (field), TREE_TYPE (field));
	  DECL_ANON_UNION_VAR_P (decl) = 1;
	  DECL_ARTIFICIAL (decl) = 1;

	  base = get_base_address (object);
	  TREE_PUBLIC (decl) = TREE_PUBLIC (base);
	  TREE_STATIC (decl) = TREE_STATIC (base);
	  DECL_EXTERNAL (decl) = DECL_EXTERNAL (base);

	  SET_DECL_VALUE_EXPR (decl, ref);
	  DECL_HAS_VALUE_EXPR_P (decl) = 1;

	  decl = pushdecl (decl);
	}
      else if (ANON_AGGR_TYPE_P (TREE_TYPE (field)))
	decl = build_anon_union_vars (TREE_TYPE (field), ref);
      else
	decl = 0;

      if (main_decl == NULL_TREE)
	main_decl = decl;
    }

  return main_decl;
}
