contains_empty_class_p (tree type)
{
  if (is_empty_class (type))
    return true;
  if (CLASS_TYPE_P (type))
    {
      tree field;
      int i;

      for (i = 0; i < CLASSTYPE_N_BASECLASSES (type); ++i)
	if (contains_empty_class_p (TYPE_BINFO_BASETYPE (type, i)))
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
