mark_all_vars_used_1 (tree *tp, int *walk_subtrees, void *data)
{
  tree t = *tp;
  enum tree_code_class c = TREE_CODE_CLASS (TREE_CODE (t));
  tree b;

  if (TREE_CODE (t) == SSA_NAME)
    t = SSA_NAME_VAR (t);

  if (IS_EXPR_CODE_CLASS (c)
      && (b = TREE_BLOCK (t)) != NULL)
    TREE_USED (b) = true;


  if (TREE_CODE (t) == TARGET_MEM_REF)
    {
      mark_all_vars_used (&TMR_BASE (t), data);
      mark_all_vars_used (&TMR_INDEX (t), data);
      mark_all_vars_used (&TMR_INDEX2 (t), data);
      *walk_subtrees = 0;
      return NULL;
    }


  if (TREE_CODE (t) == VAR_DECL)
    {
      if (data != NULL && bitmap_clear_bit ((bitmap) data, DECL_UID (t))
	  && DECL_CONTEXT (t) == current_function_decl)
	mark_all_vars_used (&DECL_INITIAL (t), data);
      set_is_used (t);
    }


  if (TREE_CODE (t) == LABEL_DECL)


    TREE_USED (t) = 1;

  if (IS_TYPE_OR_DECL_P (t))
    *walk_subtrees = 0;

  return NULL;
}
