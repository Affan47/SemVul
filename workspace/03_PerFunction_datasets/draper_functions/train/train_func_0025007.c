gcse_emit_move_after (src, dest, insn)
     rtx src, dest, insn;
{
  rtx new;
  rtx set = single_set (insn), set2;
  rtx note;
  rtx eqv;


  new = emit_insn_after (gen_move_insn (dest, src), insn);


  set2 = single_set (new);
  if (!set2 || !rtx_equal_p (SET_DEST (set2), dest))
    return new;
  if ((note = find_reg_equal_equiv_note (insn)))
    eqv = XEXP (note, 0);
  else
    eqv = SET_SRC (set);

  set_unique_reg_note (new, REG_EQUAL, copy_insn_1 (eqv));

  return new;
}
