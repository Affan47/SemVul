convert_to_pointer (tree type, tree expr)
{
  location_t loc = EXPR_LOCATION (expr);
  if (TREE_TYPE (expr) == type)
    return expr;

  switch (TREE_CODE (TREE_TYPE (expr)))
    {
    case POINTER_TYPE:
    case REFERENCE_TYPE:
      {


	addr_space_t to_as = TYPE_ADDR_SPACE (TREE_TYPE (type));
	addr_space_t from_as = TYPE_ADDR_SPACE (TREE_TYPE (TREE_TYPE (expr)));

	if (to_as == from_as)
	  return fold_build1_loc (loc, NOP_EXPR, type, expr);
	else
	  return fold_build1_loc (loc, ADDR_SPACE_CONVERT_EXPR, type, expr);
      }

    case INTEGER_TYPE:
    case ENUMERAL_TYPE:
    case BOOLEAN_TYPE:
      {


	unsigned int pprec = TYPE_PRECISION (type);
	unsigned int eprec = TYPE_PRECISION (TREE_TYPE (expr));

 	if (eprec != pprec)
	  expr = fold_build1_loc (loc, NOP_EXPR,
			      lang_hooks.types.type_for_size (pprec, 0),
			      expr);
      }

      return fold_build1_loc (loc, CONVERT_EXPR, type, expr);

    default:
      error ("cannot convert to a pointer type");
      return convert_to_pointer (type, integer_zero_node);
    }
}
