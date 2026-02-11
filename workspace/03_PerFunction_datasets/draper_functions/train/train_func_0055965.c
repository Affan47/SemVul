fold_builtin_sincos (location_t loc,
		     tree arg0, tree arg1, tree arg2)
{
  tree type;
  tree res, fn, call;

  if (!validate_arg (arg0, REAL_TYPE)
      || !validate_arg (arg1, POINTER_TYPE)
      || !validate_arg (arg2, POINTER_TYPE))
    return NULL_TREE;

  type = TREE_TYPE (arg0);


  if ((res = do_mpfr_sincos (arg0, arg1, arg2)))
    return res;


  if (!TARGET_C99_FUNCTIONS)
    return NULL_TREE;
  fn = mathfn_built_in (type, BUILT_IN_CEXPI);
  if (!fn)
    return NULL_TREE;

  call = build_call_expr_loc (loc, fn, 1, arg0);
  call = builtin_save_expr (call);

  return build2 (COMPOUND_EXPR, void_type_node,
		 build2 (MODIFY_EXPR, void_type_node,
			 build_fold_indirect_ref_loc (loc, arg1),
			 build1 (IMAGPART_EXPR, type, call)),
		 build2 (MODIFY_EXPR, void_type_node,
			 build_fold_indirect_ref_loc (loc, arg2),
			 build1 (REALPART_EXPR, type, call)));
}
