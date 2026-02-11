walk_stmt_tree (tree *tp, walk_tree_fn func, void *data)
{
  enum tree_code code;
  int walk_subtrees;
  tree result;
  int i, len;

#define WALK_SUBTREE(NODE)				\
  do							\
    {							\
      result = walk_stmt_tree (&(NODE), func, data);	\
      if (result)					\
	return result;					\
    }							\
  while (0)


  if (!*tp)
    return NULL_TREE;


  if (!STATEMENT_CODE_P (TREE_CODE (*tp)))
    return NULL_TREE;


  walk_subtrees = 1;
  result = (*func) (tp, &walk_subtrees, data);


  if (result)
    return result;


  code = TREE_CODE (*tp);
  if (!STATEMENT_CODE_P (code))
    return NULL_TREE;


  if (walk_subtrees)
    {


      len = TREE_CODE_LENGTH (code);


      for (i = 0; i < len; ++i)
	WALK_SUBTREE (TREE_OPERAND (*tp, i));
    }


  return walk_stmt_tree (&TREE_CHAIN (*tp), func, data);

#undef WALK_SUBTREE
}
