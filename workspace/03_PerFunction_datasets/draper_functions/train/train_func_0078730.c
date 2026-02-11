canonicalize_constructor_val (tree cval)
{
  STRIP_NOPS (cval);
  if (TREE_CODE (cval) == POINTER_PLUS_EXPR)
    {
      tree t = maybe_fold_offset_to_address (EXPR_LOCATION (cval),
					     TREE_OPERAND (cval, 0),
					     TREE_OPERAND (cval, 1),
					     TREE_TYPE (cval));
      if (t)
	cval = t;
    }
  if (TREE_CODE (cval) == ADDR_EXPR)
    {
      tree base = get_base_address (TREE_OPERAND (cval, 0));

      if (base
	  && (TREE_CODE (base) == VAR_DECL
	      || TREE_CODE (base) == FUNCTION_DECL)
	  && !can_refer_decl_in_current_unit_p (base))
	return NULL_TREE;
      if (base && TREE_CODE (base) == VAR_DECL)
	add_referenced_var (base);


      if (TREE_TYPE (TREE_TYPE (cval)) != TREE_TYPE (TREE_OPERAND (cval, 0)))
	cval = build_fold_addr_expr (TREE_OPERAND (cval, 0));
    }
  return cval;
}
