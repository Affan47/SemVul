assume_compiled (const char *ident)
{
  class_flag_node *i;
  int result;

  if (NULL == assume_compiled_tree)
    return 1;

  i = find_class_flag_node (assume_compiled_tree, ident);

  result = ! i->value;

  return (result);
}
