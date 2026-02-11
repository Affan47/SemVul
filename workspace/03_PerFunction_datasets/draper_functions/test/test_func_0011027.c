do_mpfr_lgamma_r (tree arg, tree arg_sg, tree type)
{
  tree result = NULL_TREE;

  STRIP_NOPS (arg);


  if (REAL_MODE_FORMAT (TYPE_MODE (type))->b == 2
      && TREE_CODE (arg) == REAL_CST && !TREE_OVERFLOW (arg)
      && TREE_CODE (TREE_TYPE (arg_sg)) == POINTER_TYPE
      && TYPE_MAIN_VARIANT (TREE_TYPE (TREE_TYPE (arg_sg))) == integer_type_node)
    {
      const REAL_VALUE_TYPE *const ra = TREE_REAL_CST_PTR (arg);


      if (real_isfinite (ra)
	  && ra->cl != rvc_zero
	  && !(real_isneg(ra) && real_isinteger(ra, TYPE_MODE (type))))
        {
	  const struct real_format *fmt = REAL_MODE_FORMAT (TYPE_MODE (type));
	  const int prec = fmt->p;
	  const mp_rnd_t rnd = fmt->round_towards_zero? GMP_RNDZ : GMP_RNDN;
	  int inexact, sg;
	  mpfr_t m;
	  tree result_lg;

	  mpfr_init2 (m, prec);
	  mpfr_from_real (m, ra, GMP_RNDN);
	  mpfr_clear_flags ();
	  inexact = mpfr_lgamma (m, &sg, m, rnd);
	  result_lg = do_mpfr_ckconv (m, type, inexact);
	  mpfr_clear (m);
	  if (result_lg)
	    {
	      tree result_sg;


	      arg_sg = build_fold_indirect_ref (arg_sg);

	      result_sg = fold_build2 (MODIFY_EXPR,
				       TREE_TYPE (arg_sg), arg_sg,
				       build_int_cst (TREE_TYPE (arg_sg), sg));
	      TREE_SIDE_EFFECTS (result_sg) = 1;

	      result = non_lvalue (fold_build2 (COMPOUND_EXPR, type,
						result_sg, result_lg));
	    }
	}
    }

  return result;
}
