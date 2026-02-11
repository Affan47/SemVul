get_ne_mm_tree(RANGE_OPT_PARAM *param, Item_func *cond_func,
                                Field *field,
                                Item *lt_value, Item *gt_value,
                                Item_result cmp_type)
{
  SEL_TREE *tree;
  tree= get_mm_parts(param, cond_func, field, Item_func::LT_FUNC,
                     lt_value, cmp_type);
  if (tree)
  {
    tree= tree_or(param, tree, get_mm_parts(param, cond_func, field,
					    Item_func::GT_FUNC,
					    gt_value, cmp_type));
  }
  return tree;
}
