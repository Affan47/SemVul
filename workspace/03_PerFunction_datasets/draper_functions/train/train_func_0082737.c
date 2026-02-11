find_bswap (gimple stmt)
{


  unsigned HOST_WIDEST_INT cmp =
    sizeof (HOST_WIDEST_INT) < 8 ? 0 :
    (unsigned HOST_WIDEST_INT)0x01020304 << 32 | 0x05060708;

  struct symbolic_number n;
  tree source_expr;


  source_expr =  find_bswap_1 (stmt, &n,
			       TREE_INT_CST_LOW (
				 TYPE_SIZE_UNIT (gimple_expr_type (stmt))) + 1);

  if (!source_expr)
    return NULL_TREE;


  if (n.size < (int)sizeof (HOST_WIDEST_INT))
    {
      unsigned HOST_WIDEST_INT mask =
	((unsigned HOST_WIDEST_INT)1 << (n.size * BITS_PER_UNIT)) - 1;

      n.n &= mask;
      cmp >>= (sizeof (HOST_WIDEST_INT) - n.size) * BITS_PER_UNIT;
    }


  if (cmp != n.n)
    return NULL_TREE;

  return source_expr;
}
