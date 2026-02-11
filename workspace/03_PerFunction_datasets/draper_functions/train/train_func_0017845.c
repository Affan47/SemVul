qualified_lookup_using_namespace (tree name, tree scope, cxx_binding *result,
                                  int flags)
{

  tree seen = NULL_TREE;

  tree todo = NULL_TREE;
  tree todo_maybe = NULL_TREE;
  tree usings;
  timevar_push (TV_NAME_LOOKUP);

  scope = ORIGINAL_NAMESPACE (scope);
  while (scope && result->value != error_mark_node)
    {
      cxx_binding *binding =
	cxx_scope_find_binding_for_name (NAMESPACE_LEVEL (scope), name);
      seen = tree_cons (scope, NULL_TREE, seen);
      if (binding)
        result = ambiguous_decl (name, result, binding, flags);


      for (usings = DECL_NAMESPACE_USING (scope); usings;
	   usings = TREE_CHAIN (usings))

	if (!TREE_INDIRECT_USING (usings))
	  {


	    if (is_associated_namespace (scope, TREE_PURPOSE (usings))
		&& !purpose_member (TREE_PURPOSE (usings), seen)
		&& !purpose_member (TREE_PURPOSE (usings), todo))
	      todo = tree_cons (TREE_PURPOSE (usings), NULL_TREE, todo);
	    else if ((!result->value && !result->type)
		     && !purpose_member (TREE_PURPOSE (usings), seen)
		     && !purpose_member (TREE_PURPOSE (usings), todo)
		     && !purpose_member (TREE_PURPOSE (usings), todo_maybe))
	      todo_maybe = tree_cons (TREE_PURPOSE (usings), NULL_TREE,
				      todo_maybe);
	  }
      if (todo)
	{
	  scope = TREE_PURPOSE (todo);
	  todo = TREE_CHAIN (todo);
	}
      else if (todo_maybe
	       && (!result->value && !result->type))
	{
	  scope = TREE_PURPOSE (todo_maybe);
	  todo = TREE_CHAIN (todo_maybe);
	  todo_maybe = NULL_TREE;
	}
      else
	scope = NULL_TREE;
    }
  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, result->value != error_mark_node);
}
