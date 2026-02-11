copy_tree_r (tree *tp, int *walk_subtrees, void *data ATTRIBUTE_UNUSED)
{
  enum tree_code code = TREE_CODE (*tp);
  enum tree_code_class cl = TREE_CODE_CLASS (code);


  if (IS_EXPR_CODE_CLASS (cl)
      || code == TREE_LIST
      || code == TREE_VEC
      || code == TYPE_DECL
      || code == OMP_CLAUSE)
    {


      tree chain = NULL_TREE, new_tree;

      if (CODE_CONTAINS_STRUCT (code, TS_COMMON))
	chain = TREE_CHAIN (*tp);


      new_tree = copy_node (*tp);


      if (flag_mudflap && mf_marked_p (*tp))
        mf_mark (new_tree);

      *tp = new_tree;


      if (code == PARM_DECL
	  || code == TREE_LIST
	  || code == OMP_CLAUSE)
	TREE_CHAIN (*tp) = chain;


      if (TREE_CODE (*tp) == BIND_EXPR)
	BIND_EXPR_BLOCK (*tp) = NULL_TREE;
    }
  else if (code == CONSTRUCTOR)
    {


      tree new_tree;

      new_tree = copy_node (*tp);


      if (flag_mudflap && mf_marked_p (*tp))
        mf_mark (new_tree);

      CONSTRUCTOR_ELTS (new_tree) = vec_safe_copy (CONSTRUCTOR_ELTS (*tp));
      *tp = new_tree;
    }
  else if (code == STATEMENT_LIST)


    copy_statement_list (tp);
  else if (TREE_CODE_CLASS (code) == tcc_type)
    *walk_subtrees = 0;
  else if (TREE_CODE_CLASS (code) == tcc_declaration)
    *walk_subtrees = 0;
  else if (TREE_CODE_CLASS (code) == tcc_constant)
    *walk_subtrees = 0;
  return NULL_TREE;
}
