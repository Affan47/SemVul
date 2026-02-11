instantiate_scev_1 (basic_block instantiate_below,
		    struct loop *evolution_loop, tree chrec,
		    bool fold_conversions, htab_t cache, int size_expr)
{
  tree op0 = instantiate_scev_r (instantiate_below, evolution_loop,
				 TREE_OPERAND (chrec, 0),
				 fold_conversions, cache, size_expr);

  if (op0 == chrec_dont_know)
    return chrec_dont_know;

  if (op0 == TREE_OPERAND (chrec, 0))
    return chrec;

  return fold_build1 (TREE_CODE (chrec), TREE_TYPE (chrec), op0);
}
