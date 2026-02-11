aggregate_type_contains_array_p (tree type)
{
  switch (TREE_CODE (type))
    {
    case RECORD_TYPE:
    case UNION_TYPE:
    case QUAL_UNION_TYPE:
      {
	tree field;
	for (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	  if (AGGREGATE_TYPE_P (TREE_TYPE (field))
	      && aggregate_type_contains_array_p (TREE_TYPE (field)))
	    return true;
	return false;
      }

    case ARRAY_TYPE:
      return true;

    default:
      gcc_unreachable ();
    }
}
