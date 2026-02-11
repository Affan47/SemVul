default_init_uninitialized_part (tree type)
{
  tree t, r, binfo;
  int i;

  type = strip_array_types (type);
  if (!CLASS_TYPE_P (type))
    return type;
  if (type_has_user_provided_default_constructor (type))
    return NULL_TREE;
  for (binfo = TYPE_BINFO (type), i = 0;
       BINFO_BASE_ITERATE (binfo, i, t); ++i)
    {
      r = default_init_uninitialized_part (BINFO_TYPE (t));
      if (r)
	return r;
    }
  for (t = TYPE_FIELDS (type); t; t = DECL_CHAIN (t))
    if (TREE_CODE (t) == FIELD_DECL
	&& !DECL_ARTIFICIAL (t)
	&& !DECL_INITIAL (t))
      {
	r = default_init_uninitialized_part (TREE_TYPE (t));
	if (r)
	  return DECL_P (r) ? r : t;
      }

  return NULL_TREE;
}
