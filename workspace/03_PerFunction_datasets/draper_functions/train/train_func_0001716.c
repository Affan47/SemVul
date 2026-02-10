is_implemented (tree name)
{
  struct imp_entry *t;
  for (t = imp_list; t; t = t->next)
    if (TREE_CODE (t->imp_context) == CLASS_IMPLEMENTATION_TYPE
	&& CLASS_NAME (t->imp_template) == name)
      return true;

  return false;
}
