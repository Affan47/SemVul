build_cplus_new (tree type, tree init)
{
  tree fn;
  tree slot;
  tree rval;
  int is_ctor;


  abstract_virtuals_error (NULL_TREE, type);

  if (TREE_CODE (init) != CALL_EXPR && TREE_CODE (init) != AGGR_INIT_EXPR)
    return convert (type, init);

  fn = TREE_OPERAND (init, 0);
  is_ctor = (TREE_CODE (fn) == ADDR_EXPR
	     && TREE_CODE (TREE_OPERAND (fn, 0)) == FUNCTION_DECL
	     && DECL_CONSTRUCTOR_P (TREE_OPERAND (fn, 0)));

  slot = build_local_temp (type);


  if (is_ctor || TREE_ADDRESSABLE (type))
    {
      rval = build (AGGR_INIT_EXPR, type, fn, TREE_OPERAND (init, 1), slot);
      TREE_SIDE_EFFECTS (rval) = 1;
      AGGR_INIT_VIA_CTOR_P (rval) = is_ctor;
    }
  else
    rval = init;

  rval = build_target_expr (slot, rval);

  return rval;
}
