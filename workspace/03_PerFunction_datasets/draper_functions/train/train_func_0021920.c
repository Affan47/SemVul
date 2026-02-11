is_gimple_lvalue (tree t)
{
  return (is_gimple_addressable (t)
	  || TREE_CODE (t) == WITH_SIZE_EXPR


	  || TREE_CODE (t) == BIT_FIELD_REF);
}
