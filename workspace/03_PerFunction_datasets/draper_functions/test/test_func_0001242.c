process_bb_node_for_hard_reg_moves (ira_loop_tree_node_t loop_tree_node)
{
  int i, freq, cost, src_regno, dst_regno, hard_regno;
  bool to_p;
  ira_allocno_t a;
  enum reg_class rclass, hard_reg_class;
  enum machine_mode mode;
  basic_block bb;
  rtx insn, set, src, dst;

  bb = loop_tree_node->bb;
  if (bb == NULL)
    return;
  freq = REG_FREQ_FROM_BB (bb);
  if (freq == 0)
    freq = 1;
  FOR_BB_INSNS (bb, insn)
    {
      if (!NONDEBUG_INSN_P (insn))
	continue;
      set = single_set (insn);
      if (set == NULL_RTX)
	continue;
      dst = SET_DEST (set);
      src = SET_SRC (set);
      if (! REG_P (dst) || ! REG_P (src))
	continue;
      dst_regno = REGNO (dst);
      src_regno = REGNO (src);
      if (dst_regno >= FIRST_PSEUDO_REGISTER
	  && src_regno < FIRST_PSEUDO_REGISTER)
	{
	  hard_regno = src_regno;
	  to_p = true;
	  a = ira_curr_regno_allocno_map[dst_regno];
	}
      else if (src_regno >= FIRST_PSEUDO_REGISTER
	       && dst_regno < FIRST_PSEUDO_REGISTER)
	{
	  hard_regno = dst_regno;
	  to_p = false;
	  a = ira_curr_regno_allocno_map[src_regno];
	}
      else
	continue;
      rclass = ALLOCNO_COVER_CLASS (a);
      if (! TEST_HARD_REG_BIT (reg_class_contents[rclass], hard_regno))
	continue;
      i = ira_class_hard_reg_index[rclass][hard_regno];
      if (i < 0)
	continue;
      mode = ALLOCNO_MODE (a);
      hard_reg_class = REGNO_REG_CLASS (hard_regno);
      cost
	= (to_p ? ira_get_register_move_cost (mode, hard_reg_class, rclass)
	   : ira_get_register_move_cost (mode, rclass, hard_reg_class)) * freq;
      ira_allocate_and_set_costs (&ALLOCNO_HARD_REG_COSTS (a), rclass,
				  ALLOCNO_COVER_CLASS_COST (a));
      ira_allocate_and_set_costs (&ALLOCNO_CONFLICT_HARD_REG_COSTS (a),
				  rclass, 0);
      ALLOCNO_HARD_REG_COSTS (a)[i] -= cost;
      ALLOCNO_CONFLICT_HARD_REG_COSTS (a)[i] -= cost;
      ALLOCNO_COVER_CLASS_COST (a) = MIN (ALLOCNO_COVER_CLASS_COST (a),
					  ALLOCNO_HARD_REG_COSTS (a)[i]);
    }
}
