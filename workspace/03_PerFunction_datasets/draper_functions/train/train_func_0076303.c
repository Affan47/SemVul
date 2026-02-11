contains_empty_class_p (tree type)
{
  if (is_empty_class (type))
    return true;
  if (CLASS_TYPE_P (type))
    {
      tree field;
      tree binfo;
      tree base_binfo;
      int i;

      for (binfo = TYPE_BINFO (type), i = 0;
	   BINFO_BASE_ITERATE (binfo, i, base_binfo); ++i)
	if (contains_empty_class_p (BINFO_TYPE (base_binfo)))
	  return true;
      for (field = TYPE_FIELDS (type); field; field = TREE_CHAIN (field))
	if (TREE_CODE (field) == FIELD_DECL
	    && !DECL_ARTIFICIAL (field)
	    && is_empty_class (TREE_TYPE (field)))
	  return true;
    }
  else if (TREE_CODE (type) == ARRAY_TYPE)
    return contains_empty_class_p (TREE_TYPE (type));
  return false;
}
