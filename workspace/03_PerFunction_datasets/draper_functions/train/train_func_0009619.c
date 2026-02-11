add_friend (tree type, tree decl, bool complain)
{
  tree typedecl;
  tree list;
  tree name;

  if (decl == error_mark_node)
    return;

  typedecl = TYPE_MAIN_DECL (type);
  list = DECL_FRIENDLIST (typedecl);
  name = DECL_NAME (decl);
  type = TREE_TYPE (typedecl);

  while (list)
    {
      if (name == FRIEND_NAME (list))
	{
	  tree friends = FRIEND_DECLS (list);
	  for (; friends ; friends = TREE_CHAIN (friends))
	    {
	      if (decl == TREE_VALUE (friends))
		{
		  if (complain)
		    warning ("`%D' is already a friend of class `%T'",
			     decl, type);
		  return;
		}
	    }

	  maybe_add_class_template_decl_list (type, decl, 1);

	  TREE_VALUE (list) = tree_cons (NULL_TREE, decl,
					 TREE_VALUE (list));
	  return;
	}
      list = TREE_CHAIN (list);
    }

  if (DECL_CLASS_SCOPE_P (decl))
    {
      tree class_binfo = TYPE_BINFO (DECL_CONTEXT (decl));
      if (!uses_template_parms (BINFO_TYPE (class_binfo)))
	perform_or_defer_access_check (class_binfo, decl);
    }

  maybe_add_class_template_decl_list (type, decl, 1);

  DECL_FRIENDLIST (typedecl)
    = tree_cons (DECL_NAME (decl), build_tree_list (NULL_TREE, decl),
		 DECL_FRIENDLIST (typedecl));
  if (!uses_template_parms (type))
    DECL_BEFRIENDING_CLASSES (decl)
      = tree_cons (NULL_TREE, type,
		   DECL_BEFRIENDING_CLASSES (decl));
}
