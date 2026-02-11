expand_doubleword_bswap (enum machine_mode mode, rtx op, rtx target)
{
  rtx t0, t1;

  t1 = expand_unop (word_mode, bswap_optab,
		    operand_subword_force (op, 0, mode), NULL_RTX, true);
  t0 = expand_unop (word_mode, bswap_optab,
		    operand_subword_force (op, 1, mode), NULL_RTX, true);

  if (target == 0 || !valid_multiword_target_p (target))
    target = gen_reg_rtx (mode);
  if (REG_P (target))
    emit_clobber (target);
  emit_move_insn (operand_subword (target, 0, 1, mode), t0);
  emit_move_insn (operand_subword (target, 1, 1, mode), t1);

  return target;
}
