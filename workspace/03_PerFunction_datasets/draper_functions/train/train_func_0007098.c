check_accessibility_of_qualified_id (tree decl,
				     tree object_type,
				     tree nested_name_specifier)
{
  tree scope;
  tree qualifying_type = NULL_TREE;


  add_typedef_to_current_template_for_access_check (decl,
						    nested_name_specifier
						    ? nested_name_specifier
						    : DECL_CONTEXT (decl),
						    input_location);


  if (deferred_access_no_check)
    return;


  scope = context_for_name_lookup (decl);

  if (!TYPE_P (scope))
    return;

  if (object_type


      && CLASS_TYPE_P (object_type)
      && DERIVED_FROM_P (scope, object_type))


    qualifying_type = object_type;
  else if (nested_name_specifier)
    {


      if (DECL_NONSTATIC_MEMBER_P (decl)
	  && current_class_ptr
	  && DERIVED_FROM_P (scope, current_class_type))
	qualifying_type = current_class_type;


      else
	qualifying_type = nested_name_specifier;
    }
  else


    qualifying_type = currently_open_derived_class (scope);

  if (qualifying_type


      && CLASS_TYPE_P (qualifying_type)
      && !dependent_type_p (qualifying_type))
    perform_or_defer_access_check (TYPE_BINFO (qualifying_type), decl,
				   decl);
}
