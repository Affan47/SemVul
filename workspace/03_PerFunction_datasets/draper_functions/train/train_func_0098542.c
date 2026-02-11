remove_attribute (const char *attr_name, tree list)
{
  tree *p;
  size_t attr_len = strlen (attr_name);

  gcc_checking_assert (attr_name[0] != '_');

  for (p = &list; *p; )
    {
      tree l = *p;


      if (private_is_attribute_p (attr_name, attr_len, get_attribute_name (l)))
	*p = TREE_CHAIN (l);
      else
	p = &TREE_CHAIN (l);
    }

  return list;
}
