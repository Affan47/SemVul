assert_no_overflow_lt (tree type, affine_iv *iv0, affine_iv *iv1,
		       struct tree_niter_desc *niter, tree step)
{
  tree bound, d, assumption, diff;
  tree niter_type = TREE_TYPE (step);

  if (integer_nonzerop (iv0->step))
    {

      if (iv0->no_overflow)
	return true;


      if (TREE_CODE (iv0->base) == INTEGER_CST)
	{
	  d = fold_build2 (MINUS_EXPR, niter_type,
			   fold_convert (niter_type, TYPE_MAX_VALUE (type)),
			   fold_convert (niter_type, iv0->base));
	  diff = fold_build2 (FLOOR_MOD_EXPR, niter_type, d, step);
	}
      else
	diff = fold_build2 (MINUS_EXPR, niter_type, step,
			    build_int_cst (niter_type, 1));
      bound = fold_build2 (MINUS_EXPR, type,
			   TYPE_MAX_VALUE (type), fold_convert (type, diff));
      assumption = fold_build2 (LE_EXPR, boolean_type_node,
				iv1->base, bound);
    }
  else
    {

      if (iv1->no_overflow)
	return true;

      if (TREE_CODE (iv1->base) == INTEGER_CST)
	{
	  d = fold_build2 (MINUS_EXPR, niter_type,
			   fold_convert (niter_type, iv1->base),
			   fold_convert (niter_type, TYPE_MIN_VALUE (type)));
	  diff = fold_build2 (FLOOR_MOD_EXPR, niter_type, d, step);
	}
      else
	diff = fold_build2 (MINUS_EXPR, niter_type, step,
			    build_int_cst (niter_type, 1));
      bound = fold_build2 (PLUS_EXPR, type,
			   TYPE_MIN_VALUE (type), fold_convert (type, diff));
      assumption = fold_build2 (GE_EXPR, boolean_type_node,
				iv0->base, bound);
    }

  if (integer_zerop (assumption))
    return false;
  if (!integer_nonzerop (assumption))
    niter->assumptions = fold_build2 (TRUTH_AND_EXPR, boolean_type_node,
				      niter->assumptions, assumption);

  iv0->no_overflow = true;
  iv1->no_overflow = true;
  return true;
}
