assert_loop_rolls_lt (tree type, affine_iv *iv0, affine_iv *iv1,
		      struct tree_niter_desc *niter, bounds *bnds)
{
  tree assumption = boolean_true_node, bound, diff;
  tree mbz, mbzl, mbzr, type1;
  bool rolls_p, no_overflow_p;
  double_int dstep;
  mpz_t mstep, max;


  if (integer_nonzerop (iv0->step))
    dstep = tree_to_double_int (iv0->step);
  else
    {
      dstep = tree_to_double_int (iv1->step).sext (TYPE_PRECISION (type));
      dstep = -dstep;
    }

  mpz_init (mstep);
  mpz_set_double_int (mstep, dstep, true);
  mpz_neg (mstep, mstep);
  mpz_add_ui (mstep, mstep, 1);

  rolls_p = mpz_cmp (mstep, bnds->below) <= 0;

  mpz_init (max);
  mpz_set_double_int (max, double_int::mask (TYPE_PRECISION (type)), true);
  mpz_add (max, max, mstep);
  no_overflow_p = (mpz_cmp (bnds->up, max) <= 0


		   || POINTER_TYPE_P (type));
  mpz_clear (mstep);
  mpz_clear (max);

  if (rolls_p && no_overflow_p)
    return;

  type1 = type;
  if (POINTER_TYPE_P (type))
    type1 = sizetype;


  if (integer_nonzerop (iv0->step))
    {
      diff = fold_build2 (MINUS_EXPR, type1,
			  iv0->step, build_int_cst (type1, 1));


      if (!POINTER_TYPE_P (type))
	{
	  bound = fold_build2 (PLUS_EXPR, type1,
			       TYPE_MIN_VALUE (type), diff);
	  assumption = fold_build2 (GE_EXPR, boolean_type_node,
				    iv0->base, bound);
	}


      mbzl = fold_build2 (MINUS_EXPR, type1,
			  fold_convert (type1, iv0->base), diff);
      mbzr = fold_convert (type1, iv1->base);
    }
  else
    {
      diff = fold_build2 (PLUS_EXPR, type1,
			  iv1->step, build_int_cst (type1, 1));

      if (!POINTER_TYPE_P (type))
	{
	  bound = fold_build2 (PLUS_EXPR, type1,
			       TYPE_MAX_VALUE (type), diff);
	  assumption = fold_build2 (LE_EXPR, boolean_type_node,
				    iv1->base, bound);
	}

      mbzl = fold_convert (type1, iv0->base);
      mbzr = fold_build2 (MINUS_EXPR, type1,
			  fold_convert (type1, iv1->base), diff);
    }

  if (!integer_nonzerop (assumption))
    niter->assumptions = fold_build2 (TRUTH_AND_EXPR, boolean_type_node,
				      niter->assumptions, assumption);
  if (!rolls_p)
    {
      mbz = fold_build2 (GT_EXPR, boolean_type_node, mbzl, mbzr);
      niter->may_be_zero = fold_build2 (TRUTH_OR_EXPR, boolean_type_node,
					niter->may_be_zero, mbz);
    }
}
