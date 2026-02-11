powi_as_mults (gimple_stmt_iterator *gsi, location_t loc,
	       tree arg0, HOST_WIDE_INT n)
{
  tree cache[POWI_TABLE_SIZE], result, type = TREE_TYPE (arg0), target;
  gimple div_stmt;

  if (n == 0)
    return build_real (type, dconst1);

  memset (cache, 0,  sizeof (cache));
  cache[1] = arg0;

  target = create_tmp_reg (type, "powmult");
  add_referenced_var (target);

  result = powi_as_mults_1 (gsi, loc, type, (n < 0) ? -n : n, cache, target);

  if (n >= 0)
    return result;


  target = make_ssa_name (target, NULL);
  div_stmt = gimple_build_assign_with_ops (RDIV_EXPR, target,
					   build_real (type, dconst1),
					   result);
  gimple_set_location (div_stmt, loc);
  gsi_insert_before (gsi, div_stmt, GSI_SAME_STMT);

  return target;
}
