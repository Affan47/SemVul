force_single_succ_latches (void)
{
  loop_iterator li;
  struct loop *loop;
  edge e;

  FOR_EACH_LOOP (li, loop, 0)
    {
      if (loop->latch != loop->header && single_succ_p (loop->latch))
	continue;

      e = find_edge (loop->latch, loop->header);

      split_edge (e);
    }
  loops_state_set (LOOPS_HAVE_SIMPLE_LATCHES);
}
