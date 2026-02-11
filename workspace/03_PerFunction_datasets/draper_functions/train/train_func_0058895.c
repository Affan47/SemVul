compute_kill (sbitmap *bb_kill, sbitmap *btr_defset,
	      HARD_REG_SET *btrs_written)
{
  int i;
  int regno;


  sbitmap_vector_zero (bb_kill, n_basic_blocks);
  for (i = 0; i < n_basic_blocks; i++)
    {
      for (regno = first_btr; regno <= last_btr; regno++)
	if (TEST_HARD_REG_BIT (all_btrs, regno)
	    && TEST_HARD_REG_BIT (btrs_written[i], regno))
	  sbitmap_a_or_b (bb_kill[i], bb_kill[i],
			  btr_defset[regno - first_btr]);
    }
}
