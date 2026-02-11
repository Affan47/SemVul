build_range_type_1 (tree type, tree lowval, tree highval, bool shared)
{
  tree itype = make_node (INTEGER_TYPE);
  hashval_t hashcode = 0;

  TREE_TYPE (itype) = type;

  TYPE_MIN_VALUE (itype) = fold_convert (type, lowval);
  TYPE_MAX_VALUE (itype) = highval ? fold_convert (type, highval) : NULL;

  TYPE_PRECISION (itype) = TYPE_PRECISION (type);
  SET_TYPE_MODE (itype, TYPE_MODE (type));
  TYPE_SIZE (itype) = TYPE_SIZE (type);
  TYPE_SIZE_UNIT (itype) = TYPE_SIZE_UNIT (type);
  TYPE_ALIGN (itype) = TYPE_ALIGN (type);
  TYPE_USER_ALIGN (itype) = TYPE_USER_ALIGN (type);

  if (!shared)
    return itype;

  if ((TYPE_MIN_VALUE (itype)
       && TREE_CODE (TYPE_MIN_VALUE (itype)) != INTEGER_CST)
      || (TYPE_MAX_VALUE (itype)
	  && TREE_CODE (TYPE_MAX_VALUE (itype)) != INTEGER_CST))
    {


      SET_TYPE_STRUCTURAL_EQUALITY (itype);
      return itype;
    }

  hashcode = iterative_hash_expr (TYPE_MIN_VALUE (itype), hashcode);
  hashcode = iterative_hash_expr (TYPE_MAX_VALUE (itype), hashcode);
  hashcode = iterative_hash_hashval_t (TYPE_HASH (type), hashcode);
  itype = type_hash_canon (hashcode, itype);

  return itype;
}
