is_friend (tree type, tree supplicant)
{
  int declp;
  tree list;
  tree context;

  if (supplicant == NULL_TREE || type == NULL_TREE)
    return 0;

  declp = DECL_P (supplicant);

  if (declp)

    {
      tree list = DECL_FRIENDLIST (TYPE_MAIN_DECL (type));
      tree name = DECL_NAME (supplicant);

      for (; list ; list = TREE_CHAIN (list))
	{
	  if (name == FRIEND_NAME (list))
	    {
	      tree friends = FRIEND_DECLS (list);
	      for (; friends ; friends = TREE_CHAIN (friends))
		{
		  tree friend = TREE_VALUE (friends);

		  if (friend == NULL_TREE)
		    continue;

		  if (supplicant == friend)
		    return 1;

		  if (is_specialization_of_friend (supplicant, friend))
		    return 1;
		}
	      break;
	    }
	}
    }
  else

    {


      for (context = supplicant;
	   context && TYPE_P (context);
	   context = TYPE_CONTEXT (context))
	if (type == context)
	  return 1;

      list = CLASSTYPE_FRIEND_CLASSES (TREE_TYPE (TYPE_MAIN_DECL (type)));
      for (; list ; list = TREE_CHAIN (list))
	{
	  tree t = TREE_VALUE (list);

	  if (TREE_CODE (t) == TEMPLATE_DECL ?
	      is_specialization_of (TYPE_MAIN_DECL (supplicant), t) :
	      same_type_p (supplicant, t))
	    return 1;
	}
    }

  if (declp && DECL_FUNCTION_MEMBER_P (supplicant))
    context = DECL_CONTEXT (supplicant);
  else if (! declp)

    context = decl_function_context (TYPE_MAIN_DECL (supplicant));
  else
    context = NULL_TREE;


  if (context && TREE_CODE (context) == NAMESPACE_DECL)
    context = NULL_TREE;

  if (context)
    return is_friend (type, context);

  return 0;
}
