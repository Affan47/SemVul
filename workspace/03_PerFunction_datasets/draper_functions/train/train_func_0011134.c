comp_ptr_ttypes_const (tree to, tree from)
{
  bool is_opaque_pointer = false;

  for (; ; to = TREE_TYPE (to), from = TREE_TYPE (from))
    {
      if (TREE_CODE (to) != TREE_CODE (from))
	return false;

      if (TREE_CODE (from) == OFFSET_TYPE
	  && same_type_p (TYPE_OFFSET_BASETYPE (from),
			  TYPE_OFFSET_BASETYPE (to)))
	  continue;

      if (TREE_CODE (to) == VECTOR_TYPE)
	is_opaque_pointer = vector_targets_convertible_p (to, from);

      if (TREE_CODE (to) != POINTER_TYPE)
	return (is_opaque_pointer
		|| same_type_ignoring_top_level_qualifiers_p (to, from));
    }
}
