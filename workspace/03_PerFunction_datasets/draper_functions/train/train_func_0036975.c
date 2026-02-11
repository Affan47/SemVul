pre_delete (void)
{
  unsigned int i;
  int changed;
  struct expr *expr;
  struct occr *occr;

  changed = 0;
  for (i = 0; i < expr_hash_table.size; i++)
    for (expr = expr_hash_table.table[i];
	 expr != NULL;
	 expr = expr->next_same_hash)
      {
	int indx = expr->bitmap_index;


	for (occr = expr->antic_occr; occr != NULL; occr = occr->next)
	  {
	    rtx insn = occr->insn;
	    rtx set;
	    basic_block bb = BLOCK_FOR_INSN (insn);


	    if (TEST_BIT (pre_delete_map[bb->index], indx)
		&& (set = single_set (insn)) != 0
                && dbg_cnt (pre_insn))
	      {


		if (expr->reaching_reg == NULL)
		  expr->reaching_reg = gen_reg_rtx_and_attrs (SET_DEST (set));

		gcse_emit_move_after (expr->reaching_reg, SET_DEST (set), insn);
		delete_insn (insn);
		occr->deleted_p = 1;
		changed = 1;
		gcse_subst_count++;

		if (dump_file)
		  {
		    fprintf (dump_file,
			     "PRE: redundant insn %d (expression %d) in ",
			       INSN_UID (insn), indx);
		    fprintf (dump_file, "bb %d, reaching reg is %d\n",
			     bb->index, REGNO (expr->reaching_reg));
		  }
	      }
	  }
      }

  return changed;
}
