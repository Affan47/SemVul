optimize_bb_for_size_p (const_basic_block bb)
{
  return optimize_function_for_size_p (cfun) || !maybe_hot_bb_p (bb);
}
