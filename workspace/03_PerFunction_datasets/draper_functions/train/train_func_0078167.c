replace_locals_op (tree *tp, int *walk_subtrees, void *data)
{
  struct walk_stmt_info *wi = (struct walk_stmt_info*) data;
  copy_body_data *id = (copy_body_data *) wi->info;
  struct pointer_map_t *st = id->decl_map;
  tree *n;
  tree expr = *tp;


  if ((TREE_CODE (expr) == VAR_DECL
       && !TREE_STATIC (expr))
      || TREE_CODE (expr) == LABEL_DECL)
    {

      n = (tree *) pointer_map_contains (st, expr);


      if (n)
	*tp = *n;
      *walk_subtrees = 0;
    }
  else if (TREE_CODE (expr) == STATEMENT_LIST
	   || TREE_CODE (expr) == BIND_EXPR
	   || TREE_CODE (expr) == SAVE_EXPR)
    gcc_unreachable ();
  else if (TREE_CODE (expr) == TARGET_EXPR)
    {


      if (!TREE_OPERAND (expr, 1))
	{
	  TREE_OPERAND (expr, 1) = TREE_OPERAND (expr, 3);
	  TREE_OPERAND (expr, 3) = NULL_TREE;
	}
    }


  return NULL_TREE;
}
