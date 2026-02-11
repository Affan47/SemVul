build_index_type (maxval)
     tree maxval;
{
  tree itype = make_node (INTEGER_TYPE);

  TREE_TYPE (itype) = sizetype;
  TYPE_PRECISION (itype) = TYPE_PRECISION (sizetype);
  TYPE_MIN_VALUE (itype) = size_zero_node;
  TYPE_MAX_VALUE (itype) = convert (sizetype, maxval);
  TYPE_MODE (itype) = TYPE_MODE (sizetype);
  TYPE_SIZE (itype) = TYPE_SIZE (sizetype);
  TYPE_SIZE_UNIT (itype) = TYPE_SIZE_UNIT (sizetype);
  TYPE_ALIGN (itype) = TYPE_ALIGN (sizetype);
  TYPE_USER_ALIGN (itype) = TYPE_USER_ALIGN (sizetype);

  if (host_integerp (maxval, 1))
    return type_hash_canon (tree_low_cst (maxval, 1), itype);
  else
    return itype;
}
