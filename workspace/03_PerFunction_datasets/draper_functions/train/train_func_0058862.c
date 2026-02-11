arg_assoc_class_only (struct arg_lookup *k, tree type)
{
  tree list, friends, context;


  if (!CLASS_TYPE_P (type))
    return false;

  context = decl_namespace_context (type);
  if (arg_assoc_namespace (k, context))
    return true;

  complete_type (type);


  for (list = DECL_FRIENDLIST (TYPE_MAIN_DECL (type)); list;
       list = TREE_CHAIN (list))
    if (k->name == FRIEND_NAME (list))
      for (friends = FRIEND_DECLS (list); friends;
	   friends = TREE_CHAIN (friends))
	{
	  tree fn = TREE_VALUE (friends);


	  if (CP_DECL_CONTEXT (fn) != context)
	    continue;


	  if (TREE_CODE (fn) == FUNCTION_DECL && DECL_USE_TEMPLATE (fn))
	    continue;
	  if (add_function (k, fn))
	    return true;
	}

  return false;
}
