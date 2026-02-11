sched_create_recovery_edges (basic_block first_bb, basic_block rec,
			     basic_block second_bb)
{
  rtx label;
  rtx jump;
  int edge_flags;


  if (BB_PARTITION (first_bb) != BB_PARTITION (rec))

    edge_flags = EDGE_CROSSING;
  else
    edge_flags = 0;

  make_edge (first_bb, rec, edge_flags);
  label = block_label (second_bb);
  jump = emit_jump_insn_after (gen_jump (label), BB_END (rec));
  JUMP_LABEL (jump) = label;
  LABEL_NUSES (label)++;

  if (BB_PARTITION (second_bb) != BB_PARTITION (rec))

    {

      if (flag_reorder_blocks_and_partition
	  && targetm_common.have_named_sections)
	{


	  add_reg_note (jump, REG_CROSSING_JUMP, NULL_RTX);
	}
      edge_flags = EDGE_CROSSING;
    }
  else
    edge_flags = 0;

  make_single_succ_edge (rec, second_bb, edge_flags);
  if (dom_info_available_p (CDI_DOMINATORS))
    set_immediate_dominator (CDI_DOMINATORS, rec, first_bb);
}
