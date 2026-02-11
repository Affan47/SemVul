replace_store_insn (rtx reg, rtx del, basic_block bb, struct st_expr *smexpr)
{
  rtx insn, mem, note, set, ptr;

  mem = smexpr->pattern;
  insn = gen_move_insn (reg, SET_SRC (single_set (del)));

  for (ptr = smexpr->antic_stores; ptr; ptr = XEXP (ptr, 1))
    if (XEXP (ptr, 0) == del)
      {
	XEXP (ptr, 0) = insn;
	break;
      }


  REG_NOTES (insn) = REG_NOTES (del);


  insn = emit_insn_after (insn, del);

  if (dump_file)
    {
      fprintf (dump_file,
	       "STORE_MOTION  delete insn in BB %d:\n      ", bb->index);
      print_inline_rtx (dump_file, del, 6);
      fprintf (dump_file, "\nSTORE_MOTION  replaced with insn:\n      ");
      print_inline_rtx (dump_file, insn, 6);
      fprintf (dump_file, "\n");
    }

  delete_insn (del);


  for (; insn != NEXT_INSN (BB_END (bb)); insn = NEXT_INSN (insn))
    if (NONDEBUG_INSN_P (insn))
      {
	set = single_set (insn);
	if (!set)
	  continue;
	if (exp_equiv_p (SET_DEST (set), mem, 0, true))
	  return;
	note = find_reg_equal_equiv_note (insn);
	if (!note || !exp_equiv_p (XEXP (note, 0), mem, 0, true))
	  continue;

	if (dump_file)
	  fprintf (dump_file, "STORE_MOTION  drop REG_EQUAL note at insn %d:\n",
		   INSN_UID (insn));
	remove_note (insn, note);
      }
  remove_reachable_equiv_notes (bb, smexpr);
}
