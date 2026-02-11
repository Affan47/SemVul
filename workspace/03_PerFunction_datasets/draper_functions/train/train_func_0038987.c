gimplify_init_ctor_preeval_1 (tree *tp, int *walk_subtrees, void *xdata)
{
  struct gimplify_init_ctor_preeval_data *data
    = (struct gimplify_init_ctor_preeval_data *) xdata;
  tree t = *tp;


  if (data->lhs_base_decl == t)
    return t;


  if ((INDIRECT_REF_P (t)
       || TREE_CODE (t) == MEM_REF)
      && (!data->lhs_base_decl || TREE_ADDRESSABLE (data->lhs_base_decl))
      && alias_sets_conflict_p (data->lhs_alias_set, get_alias_set (t)))
    return t;


  if (TREE_CODE (t) == CALL_EXPR)
    {
      tree type, fntype = TREE_TYPE (TREE_TYPE (CALL_EXPR_FN (t)));

      for (type = TYPE_ARG_TYPES (fntype); type; type = TREE_CHAIN (type))
	if (POINTER_TYPE_P (TREE_VALUE (type))
	    && (!data->lhs_base_decl || TREE_ADDRESSABLE (data->lhs_base_decl))
	    && alias_sets_conflict_p (data->lhs_alias_set,
				      get_alias_set
				        (TREE_TYPE (TREE_VALUE (type)))))
	  return t;
    }

  if (IS_TYPE_OR_DECL_P (t))
    *walk_subtrees = 0;
  return NULL;
}
