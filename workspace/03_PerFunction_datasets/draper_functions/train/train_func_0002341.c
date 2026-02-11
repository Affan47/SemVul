record_out_operands (rtx insn, bool earlyclobber)
{
  int n_ops = recog_data.n_operands;
  int alt = which_alternative;

  int i;

  for (i = 0; i < n_ops + recog_data.n_dups; i++)
    {
      int opn = i < n_ops ? i : recog_data.dup_num[i - n_ops];
      rtx *loc = (i < n_ops
		  ? recog_data.operand_loc[opn]
		  : recog_data.dup_loc[i - n_ops]);
      rtx op = *loc;
      enum reg_class cl = recog_op_alt[opn][alt].cl;

      struct du_head *prev_open;

      if (recog_data.operand_type[opn] != OP_OUT
	  || recog_op_alt[opn][alt].earlyclobber != earlyclobber)
	continue;

      prev_open = open_chains;
      scan_rtx (insn, loc, cl, mark_write, OP_OUT);


      if (CALL_P (insn)
	  || (asm_noperands (PATTERN (insn)) > 0
	      && REG_P (op)
	      && REGNO (op) == ORIGINAL_REGNO (op)))
	{
	  if (prev_open != open_chains)
	    open_chains->cannot_rename = 1;
	}
    }
}
