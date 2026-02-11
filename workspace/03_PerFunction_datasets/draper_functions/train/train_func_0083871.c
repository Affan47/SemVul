promote_type (tree type)
{
  switch (TREE_CODE (type))
    {
    case RECORD_TYPE:
      return build_pointer_type (type);
    case BOOLEAN_TYPE:
      if (type == boolean_type_node)
	return promoted_boolean_type_node;
      goto handle_int;
    case INTEGER_TYPE:
      if (type == char_type_node)
	return promoted_char_type_node;
    handle_int:
      if (TYPE_PRECISION (type) < TYPE_PRECISION (int_type_node))
	{
	  if (type == short_type_node)
	    return promoted_short_type_node;
	  if (type == byte_type_node)
	    return promoted_byte_type_node;
	  return int_type_node;
	}

    default:
      return type;
    }
}
