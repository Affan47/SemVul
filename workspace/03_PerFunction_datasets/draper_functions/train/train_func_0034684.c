clear_aux_for_edges ()
{
  basic_block bb;
  edge e;

  FOR_BB_BETWEEN (bb, ENTRY_BLOCK_PTR, EXIT_BLOCK_PTR, next_bb)
    {
      for (e = bb->succ; e; e = e->succ_next)
	e->aux = NULL;
    }
}
