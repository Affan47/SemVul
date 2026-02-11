comp_ptr_ttypes_real (tree to, tree from, int constp)
{
  bool to_more_cv_qualified = false;
  bool is_opaque_pointer = false;

  for (; ; to = TREE_TYPE (to), from = TREE_TYPE (from))
    {
      if (TREE_CODE (to) != TREE_CODE (from))
	return 0;

      if (TREE_CODE (from) == OFFSET_TYPE
	  && !same_type_p (TYPE_OFFSET_BASETYPE (from),
			   TYPE_OFFSET_BASETYPE (to)))
	return 0;


      if (TREE_CODE (to) != FUNCTION_TYPE && TREE_CODE (to) != METHOD_TYPE)
	{
	  if (!at_least_as_qualified_p (to, from))
	    return 0;

	  if (!at_least_as_qualified_p (from, to))
	    {
	      if (constp == 0)
		return 0;
	      to_more_cv_qualified = true;
	    }

	  if (constp > 0)
	    constp &= TYPE_READONLY (to);
	}

      if (TREE_CODE (to) == VECTOR_TYPE)
	is_opaque_pointer = vector_targets_convertible_p (to, from);

      if (TREE_CODE (to) != POINTER_TYPE && !TYPE_PTRDATAMEM_P (to))
	return ((constp >= 0 || to_more_cv_qualified)
		&& (is_opaque_pointer
		    || same_type_ignoring_top_level_qualifiers_p (to, from)));
    }
}
