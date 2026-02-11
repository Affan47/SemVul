compute_subscript_distance (struct data_dependence_relation *ddr)
{
  conflict_function *cf_a, *cf_b;
  affine_fn fn_a, fn_b, diff;

  if (DDR_ARE_DEPENDENT (ddr) == NULL_TREE)
    {
      unsigned int i;

      for (i = 0; i < DDR_NUM_SUBSCRIPTS (ddr); i++)
 	{
 	  struct subscript *subscript;

 	  subscript = DDR_SUBSCRIPT (ddr, i);
 	  cf_a = SUB_CONFLICTS_IN_A (subscript);
 	  cf_b = SUB_CONFLICTS_IN_B (subscript);

	  fn_a = common_affine_function (cf_a);
	  fn_b = common_affine_function (cf_b);
	  if (!fn_a.exists () || !fn_b.exists ())
	    {
	      SUB_DISTANCE (subscript) = chrec_dont_know;
	      return;
	    }
	  diff = affine_fn_minus (fn_a, fn_b);

 	  if (affine_function_constant_p (diff))
 	    SUB_DISTANCE (subscript) = affine_function_base (diff);
 	  else
 	    SUB_DISTANCE (subscript) = chrec_dont_know;

	  affine_fn_free (diff);
 	}
    }
}
