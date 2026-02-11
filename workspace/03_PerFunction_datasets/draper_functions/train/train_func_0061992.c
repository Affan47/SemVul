ignore_bb_p (const_basic_block bb)
{
  gimple g;

  if (bb->index < NUM_FIXED_BLOCKS)
    return true;
  if (optimize_bb_for_size_p (bb))
    return true;


  g = last_stmt (CONST_CAST_BB (bb));
  if (g && gimple_code (g) == GIMPLE_TRANSACTION)
    return true;

  return false;
}
