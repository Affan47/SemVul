has_static_fields (const_tree type)
{
  tree tmp;

  for (tmp = TYPE_FIELDS (type); tmp; tmp = TREE_CHAIN (tmp))
    {
      if (DECL_NAME (tmp) && TREE_STATIC (tmp))
	return true;
    }
  return false;
}
