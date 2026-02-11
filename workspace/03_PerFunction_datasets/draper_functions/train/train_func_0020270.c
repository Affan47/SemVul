record_nonwrapping_iv (struct loop *loop, tree base, tree step, gimple stmt,
		       tree low, tree high, bool realistic, bool upper)
{
  tree niter_bound, extreme, delta;
  tree type = TREE_TYPE (base), unsigned_type;
  double_int max;

  if (TREE_CODE (step) != INTEGER_CST || integer_zerop (step))
    return;

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "Induction variable (");
      print_generic_expr (dump_file, TREE_TYPE (base), TDF_SLIM);
      fprintf (dump_file, ") ");
      print_generic_expr (dump_file, base, TDF_SLIM);
      fprintf (dump_file, " + ");
      print_generic_expr (dump_file, step, TDF_SLIM);
      fprintf (dump_file, " * iteration does not wrap in statement ");
      print_gimple_stmt (dump_file, stmt, 0, TDF_SLIM);
      fprintf (dump_file, " in loop %d.\n", loop->num);
    }

  unsigned_type = unsigned_type_for (type);
  base = fold_convert (unsigned_type, base);
  step = fold_convert (unsigned_type, step);

  if (tree_int_cst_sign_bit (step))
    {
      extreme = fold_convert (unsigned_type, low);
      if (TREE_CODE (base) != INTEGER_CST)
	base = fold_convert (unsigned_type, high);
      delta = fold_build2 (MINUS_EXPR, unsigned_type, base, extreme);
      step = fold_build1 (NEGATE_EXPR, unsigned_type, step);
    }
  else
    {
      extreme = fold_convert (unsigned_type, high);
      if (TREE_CODE (base) != INTEGER_CST)
	base = fold_convert (unsigned_type, low);
      delta = fold_build2 (MINUS_EXPR, unsigned_type, extreme, base);
    }


  niter_bound = fold_build2 (FLOOR_DIV_EXPR, unsigned_type, delta, step);
  max = derive_constant_upper_bound (niter_bound);
  record_estimate (loop, niter_bound, max, stmt, false, realistic, upper);
}
