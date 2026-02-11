tm_memopt_clear_visited (VEC (basic_block, heap) *blocks)
{
  size_t i;
  basic_block bb;

  for (i = 0; VEC_iterate (basic_block, blocks, i, bb); ++i)
    BB_VISITED_P (bb) = false;
}
