eliminate_partially_redundant_loads (void)
{
  rtx insn;
  basic_block bb;


  if (ENTRY_BLOCK_PTR->next_bb == EXIT_BLOCK_PTR)
    return;

  FOR_BB_BETWEEN (bb,
		  ENTRY_BLOCK_PTR->next_bb->next_bb,
		  EXIT_BLOCK_PTR,
		  next_bb)
    {

      if (! bb_has_well_behaved_predecessors (bb))
	continue;


      if (optimize_bb_for_size_p (bb))
	continue;


      reset_opr_set_tables ();


      FOR_BB_INSNS (bb, insn)
	{

	  if (NONJUMP_INSN_P (insn)
              && GET_CODE (PATTERN (insn)) == SET
	      && REG_P (SET_DEST (PATTERN (insn)))
	      && MEM_P (SET_SRC (PATTERN (insn))))
	    {
	      rtx pat = PATTERN (insn);
	      rtx src = SET_SRC (pat);
	      struct expr *expr;

	      if (!MEM_VOLATILE_P (src)
		  && GET_MODE (src) != BLKmode
		  && general_operand (src, GET_MODE (src))


		  && oprs_unchanged_p (src, insn, false)
		  && !(cfun->can_throw_non_call_exceptions && may_trap_p (src))
		  && !side_effects_p (src)

		  && (expr = lookup_expr_in_table (src)) != NULL)
		{


		  eliminate_partially_redundant_load (bb, insn, expr);
		}
	    }


	  if (INSN_P (insn))
	    record_opr_changes (insn);
	}
    }

  commit_edge_insertions ();
}
