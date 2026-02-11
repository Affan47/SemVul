layout_class_method (tree this_class, tree super_class,
		     tree method_decl, tree dtable_count)
{
  tree method_name = DECL_NAME (method_decl);

  TREE_PUBLIC (method_decl) = 1;

  if (flag_indirect_classes
      || (METHOD_PRIVATE (method_decl) && METHOD_STATIC (method_decl)
	  && ! METHOD_NATIVE (method_decl)
	  && ! special_method_p (method_decl)))
    java_hide_decl (method_decl);


  if (!DECL_EXTERNAL (method_decl))
    DECL_EXTERNAL (method_decl) = ((is_compiled_class (this_class) != 2)
                                   || METHOD_NATIVE (method_decl));

  if (ID_INIT_P (method_name))
    {
      const char *p = IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (this_class)));
      const char *ptr;
      for (ptr = p; *ptr; )
	{
	  if (*ptr++ == '.')
	    p = ptr;
	}
      DECL_CONSTRUCTOR_P (method_decl) = 1;
      build_java_signature (TREE_TYPE (method_decl));
    }
  else if (! METHOD_STATIC (method_decl))
    {
      tree method_sig =
	build_java_signature (TREE_TYPE (method_decl));
      bool method_override = false;
      tree super_method = lookup_java_method (super_class, method_name,
						  method_sig);
      if (super_method != NULL_TREE
	  && ! METHOD_DUMMY (super_method))
        {
	  method_override = true;
	  if (! METHOD_PUBLIC (super_method) &&
	      ! METHOD_PROTECTED (super_method))
	    {


	      if (METHOD_PRIVATE (super_method) ||
		  ! in_same_package (TYPE_NAME (this_class),
				     TYPE_NAME (super_class)))
		method_override = false;
	   }
	}
      if (method_override)
	{
	  tree method_index = get_method_index (super_method);
	  set_method_index (method_decl, method_index);
	  if (method_index == NULL_TREE
	      && ! flag_indirect_dispatch
	      && ! DECL_ARTIFICIAL (super_method))
	    error ("non-static method %q+D overrides static method",
                   method_decl);
	}
      else if (this_class == object_type_node
	       && (METHOD_FINAL (method_decl)
		   || METHOD_PRIVATE (method_decl)))
	{


	}
      else if (! METHOD_PRIVATE (method_decl)
	       && dtable_count)
	{


	  set_method_index (method_decl, dtable_count);
	  dtable_count = fold_build2 (PLUS_EXPR, integer_type_node,
				      dtable_count, integer_one_node);
	}
    }

  return dtable_count;
}
