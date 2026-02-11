ptr_reasonably_similar (const_tree to, const_tree from)
{
  for (; ; to = TREE_TYPE (to), from = TREE_TYPE (from))
    {

      if (TREE_CODE (to) == VOID_TYPE)
	return !error_type_p (from);
      if (TREE_CODE (from) == VOID_TYPE)
	return !error_type_p (to);

      if (TREE_CODE (to) != TREE_CODE (from))
	return 0;

      if (TREE_CODE (from) == OFFSET_TYPE
	  && comptypes (TYPE_OFFSET_BASETYPE (to),
			TYPE_OFFSET_BASETYPE (from),
			COMPARE_BASE | COMPARE_DERIVED))
	continue;

      if (TREE_CODE (to) == VECTOR_TYPE
	  && vector_types_convertible_p (to, from, false))
	return 1;

      if (TREE_CODE (to) == INTEGER_TYPE
	  && TYPE_PRECISION (to) == TYPE_PRECISION (from))
	return 1;

      if (TREE_CODE (to) == FUNCTION_TYPE)
	return !error_type_p (to) && !error_type_p (from);

      if (TREE_CODE (to) != POINTER_TYPE)
	return comptypes
	  (TYPE_MAIN_VARIANT (to), TYPE_MAIN_VARIANT (from),
	   COMPARE_BASE | COMPARE_DERIVED);
    }
}
