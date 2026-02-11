ipa_type_escape_star_count_of_interesting_or_array_type (tree type)
{
  int count = 0;

  if (!type)
    return -1;
  type = TYPE_MAIN_VARIANT (type);
  while (POINTER_TYPE_P (type) || TREE_CODE (type) == ARRAY_TYPE)
    {
      type = TYPE_MAIN_VARIANT (TREE_TYPE (type));
      count++;
    }


  if (TREE_CODE (type) == RECORD_TYPE
      || TREE_CODE (type) == QUAL_UNION_TYPE
      || TREE_CODE (type) == UNION_TYPE)
    return count;
  else
    return -1;
}
