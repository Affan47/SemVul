type_promotes_to (tree type)
{
  if (type == error_mark_node)
    return error_mark_node;

  type = TYPE_MAIN_VARIANT (type);


  if (type == boolean_type_node)
    type = integer_type_node;


  else if (TREE_CODE (type) == ENUMERAL_TYPE
	   || type == wchar_type_node)
    {
      int precision = MAX (TYPE_PRECISION (type),
			   TYPE_PRECISION (integer_type_node));
      tree totype = c_common_type_for_size (precision, 0);
      if (TREE_UNSIGNED (type)
	  && ! int_fits_type_p (TYPE_MAX_VALUE (type), totype))
	type = c_common_type_for_size (precision, 1);
      else
	type = totype;
    }
  else if (c_promoting_integer_type_p (type))
    {

      if (TREE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_node))
	type = unsigned_type_node;
      else
	type = integer_type_node;
    }
  else if (type == float_type_node)
    type = double_type_node;

  return type;
}
