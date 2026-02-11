sel_finish_global_and_expr (void)
{
  {
    bb_vec_t bbs;
    int i;

    bbs = VEC_alloc (basic_block, heap, current_nr_blocks);

    for (i = 0; i < current_nr_blocks; i++)
      VEC_quick_push (basic_block, bbs, BASIC_BLOCK (BB_TO_BLOCK (i)));


    {
      const struct sched_scan_info_def ssi =
	{
	  NULL,
	  finish_global_and_expr_for_bb,
	  NULL,
	  finish_global_and_expr_insn
	};

      sched_scan (&ssi, bbs, NULL, NULL, NULL);
    }

    VEC_free (basic_block, heap, bbs);
  }

  finish_insns ();
}
