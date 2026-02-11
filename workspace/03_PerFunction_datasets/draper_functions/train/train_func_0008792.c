fortran_common (tree decl, HOST_WIDE_INT *value)
{
  tree val_expr, cvar;
  enum machine_mode mode;
  HOST_WIDE_INT bitsize, bitpos;
  tree offset;
  int unsignedp, volatilep = 0;


  if (TREE_CODE (decl) != VAR_DECL
      || !TREE_STATIC (decl)
      || !DECL_HAS_VALUE_EXPR_P (decl)
      || !is_fortran ())
    return NULL_TREE;

  val_expr = DECL_VALUE_EXPR (decl);
  if (TREE_CODE (val_expr) != COMPONENT_REF)
    return NULL_TREE;

  cvar = get_inner_reference (val_expr, &bitsize, &bitpos, &offset,
			      &mode, &unsignedp, &volatilep, true);

  if (cvar == NULL_TREE
      || TREE_CODE (cvar) != VAR_DECL
      || DECL_ARTIFICIAL (cvar)
      || !TREE_PUBLIC (cvar))
    return NULL_TREE;

  *value = 0;
  if (offset != NULL)
    {
      if (!host_integerp (offset, 0))
	return NULL_TREE;
      *value = tree_low_cst (offset, 0);
    }
  if (bitpos != 0)
    *value += bitpos / BITS_PER_UNIT;

  return cvar;
}
