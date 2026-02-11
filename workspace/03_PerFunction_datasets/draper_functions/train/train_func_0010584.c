template_parm_this_level_p (tree t, void* data)
{
  int this_level = *(int *)data;
  int level;

  if (TREE_CODE (t) == TEMPLATE_PARM_INDEX)
    level = TEMPLATE_PARM_LEVEL (t);
  else
    level = TEMPLATE_TYPE_LEVEL (t);
  return level == this_level;
}
