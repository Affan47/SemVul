vector_types_convertible_p (tree t1, tree t2)
{
  return targetm.vector_opaque_p (t1)
	 || targetm.vector_opaque_p (t2)
         || (tree_int_cst_equal (TYPE_SIZE (t1), TYPE_SIZE (t2))
	     && INTEGRAL_TYPE_P (TREE_TYPE (t1))
		== INTEGRAL_TYPE_P (TREE_TYPE (t2)));
}
