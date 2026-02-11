h8300_os_task_function_p (tree func)
{
  tree a;

  if (TREE_CODE (func) != FUNCTION_DECL)
    return 0;

  a = lookup_attribute ("OS_Task", DECL_ATTRIBUTES (func));
  return a != NULL_TREE;
}
