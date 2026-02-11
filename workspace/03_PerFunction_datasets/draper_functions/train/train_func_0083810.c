pos_from_bit (tree *poffset, tree *pbitpos, unsigned int off_align,
	      tree pos)
{
  tree toff_align = bitsize_int (off_align);
  if (TREE_CODE (pos) == MULT_EXPR
      && tree_int_cst_equal (TREE_OPERAND (pos, 1), toff_align))
    {
      *poffset = size_binop (MULT_EXPR,
			     fold_convert (sizetype, TREE_OPERAND (pos, 0)),
			     size_int (off_align / BITS_PER_UNIT));
      *pbitpos = bitsize_zero_node;
    }
  else
    {
      *poffset = size_binop (MULT_EXPR,
			     fold_convert (sizetype,
					   size_binop (FLOOR_DIV_EXPR, pos,
						       toff_align)),
			     size_int (off_align / BITS_PER_UNIT));
      *pbitpos = size_binop (FLOOR_MOD_EXPR, pos, toff_align);
    }
}
