add_one_base_init (tree binfo, tree parm, bool move_p, tree inh,
		   tree member_init_list)
{
  tree init;
  if (inh)
    {


      if (BINFO_TYPE (binfo) != inh)
	return member_init_list;

      tree *p = &init;
      init = NULL_TREE;
      for (; parm; parm = DECL_CHAIN (parm))
	{
	  tree exp = convert_from_reference (parm);
	  if (TREE_CODE (TREE_TYPE (parm)) != REFERENCE_TYPE
	      || TYPE_REF_IS_RVALUE (TREE_TYPE (parm)))
	    exp = move (exp);
	  *p = build_tree_list (NULL_TREE, exp);
	  p = &TREE_CHAIN (*p);
	}
    }
  else
    {
      init = build_base_path (PLUS_EXPR, parm, binfo, 1,
			      tf_warning_or_error);
      if (move_p)
	init = move (init);
      init = build_tree_list (NULL_TREE, init);
    }
  return tree_cons (binfo, init, member_init_list);
}
