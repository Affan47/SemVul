find_reachable_label_1 (tree *tp, int *walk_subtrees ATTRIBUTE_UNUSED,
			void *data ATTRIBUTE_UNUSED)
{
  switch (TREE_CODE (*tp))
    {
    case LABEL_STMT:
    case CASE_LABEL:
      return *tp;

    default:
      break;
    }
  return NULL_TREE;
}
