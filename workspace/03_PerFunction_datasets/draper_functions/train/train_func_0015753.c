compute_frequency_overlap (void)
{
  gcov_type count_total = 0, freq_total = 0;
  int overlap = 0;
  basic_block bb;

  FOR_BB_BETWEEN (bb, ENTRY_BLOCK_PTR, NULL, next_bb)
    {
      count_total += bb->count;
      freq_total += bb->frequency;
    }

  if (count_total == 0 || freq_total == 0)
    return 0;

  FOR_BB_BETWEEN (bb, ENTRY_BLOCK_PTR, NULL, next_bb)
    overlap += MIN (bb->count * OVERLAP_BASE / count_total,
		    bb->frequency * OVERLAP_BASE / freq_total);

  return overlap;
}
