end_of_base (tree binfo)
{
  tree size;

  if (!CLASSTYPE_AS_BASE (BINFO_TYPE (binfo)))
    size = TYPE_SIZE_UNIT (char_type_node);
  else if (is_empty_class (BINFO_TYPE (binfo)))


    size = TYPE_SIZE_UNIT (BINFO_TYPE (binfo));
  else
    size = CLASSTYPE_SIZE_UNIT (BINFO_TYPE (binfo));

  return size_binop (PLUS_EXPR, BINFO_OFFSET (binfo), size);
}
