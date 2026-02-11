emit_moves (void)
{
  basic_block bb;
  edge_iterator ei;
  edge e;
  rtx insns, tmp;

  FOR_EACH_BB (bb)
    {
      if (at_bb_start[bb->index] != NULL)
	{
	  at_bb_start[bb->index] = modify_move_list (at_bb_start[bb->index]);
	  insns = emit_move_list (at_bb_start[bb->index],
				  REG_FREQ_FROM_BB (bb));
	  tmp = BB_HEAD (bb);
	  if (LABEL_P (tmp))
	    tmp = NEXT_INSN (tmp);
	  if (NOTE_INSN_BASIC_BLOCK_P (tmp))
	    tmp = NEXT_INSN (tmp);
	  if (tmp == BB_HEAD (bb))
	    emit_insn_before (insns, tmp);
	  else if (tmp != NULL_RTX)
	    emit_insn_after (insns, PREV_INSN (tmp));
	  else
	    emit_insn_after (insns, get_last_insn ());
	}

      if (at_bb_end[bb->index] != NULL)
	{
	  at_bb_end[bb->index] = modify_move_list (at_bb_end[bb->index]);
	  insns = emit_move_list (at_bb_end[bb->index], REG_FREQ_FROM_BB (bb));
	  ira_assert (! control_flow_insn_p (BB_END (bb)));
	  emit_insn_after (insns, BB_END (bb));
	}

      FOR_EACH_EDGE (e, ei, bb->succs)
	{
	  if (e->aux == NULL)
	    continue;
	  ira_assert ((e->flags & EDGE_ABNORMAL) == 0
		      || ! EDGE_CRITICAL_P (e));
	  e->aux = modify_move_list ((move_t) e->aux);
	  insert_insn_on_edge
	    (emit_move_list ((move_t) e->aux,
			     REG_FREQ_FROM_EDGE_FREQ (EDGE_FREQUENCY (e))),
	     e);
	  if (e->src->next_bb != e->dest)
	    ira_additional_jumps_num++;
	}
    }
}
