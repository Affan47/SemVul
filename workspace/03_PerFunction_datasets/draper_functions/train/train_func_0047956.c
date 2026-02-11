add_reg_crossing_jump_notes (void)
{
  basic_block bb;
  edge e;
  edge_iterator ei;

  FOR_EACH_BB (bb)
    FOR_EACH_EDGE (e, ei, bb->succs)
      if ((e->flags & EDGE_CROSSING)
	  && JUMP_P (BB_END (e->src)))
	add_reg_note (BB_END (e->src), REG_CROSSING_JUMP, NULL_RTX);
}
