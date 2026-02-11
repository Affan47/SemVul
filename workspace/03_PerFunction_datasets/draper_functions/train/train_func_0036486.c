gcse_emit_move_after (rtx dest, rtx src, rtx insn)
{
  rtx new_rtx;
  rtx set = single_set (insn), set2;
  rtx note;
  rtx eqv = NULL_RTX;


  new_rtx = emit_insn_after (gen_move_insn (dest, src), insn);


  set2 = single_set (new_rtx);
  if (!set2 || !rtx_equal_p (SET_DEST (set2), dest))
    return new_rtx;
  if ((note = find_reg_equal_equiv_note (insn)))
    eqv = XEXP (note, 0);
  else if (! REG_P (dest)
	   || ! reg_mentioned_p (dest, SET_SRC (set)))
    eqv = SET_SRC (set);

  if (eqv != NULL_RTX)
    set_unique_reg_note (new_rtx, REG_EQUAL, copy_insn_1 (eqv));

  return new_rtx;
}
