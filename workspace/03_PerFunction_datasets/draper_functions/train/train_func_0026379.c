array_type_nelts (type)
     tree type;
{
  tree index_type, min, max;


  if (! TYPE_DOMAIN (type))
    return error_mark_node;

  index_type = TYPE_DOMAIN (type);
  min = TYPE_MIN_VALUE (index_type);
  max = TYPE_MAX_VALUE (index_type);

  return (integer_zerop (min)
	  ? max
	  : fold (build (MINUS_EXPR, TREE_TYPE (max), max, min)));
}
