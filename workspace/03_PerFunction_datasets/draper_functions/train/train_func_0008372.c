null_ptr_cst_p (tree t)
{


  if (NULLPTR_TYPE_P (TREE_TYPE (t)))
    return true;
  if (CP_INTEGRAL_TYPE_P (TREE_TYPE (t)))
    {

      if (cxx_dialect < cxx0x)
	t = maybe_constant_value (fold_non_dependent_expr_sfinae (t, tf_none));
      STRIP_NOPS (t);
      if (integer_zerop (t) && !TREE_OVERFLOW (t))
	return true;
    }
  return false;
}
