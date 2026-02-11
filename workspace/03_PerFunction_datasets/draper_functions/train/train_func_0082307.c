contains_auto_r (tree *tp, int *walk_subtrees ATTRIBUTE_UNUSED,
		 void *type)
{

  if (DECL_P (*tp)
      && TREE_TYPE (*tp) == type)
    return *tp;
  else
    return NULL_TREE;
}
