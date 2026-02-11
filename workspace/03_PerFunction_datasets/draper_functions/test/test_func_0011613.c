gen_split_228 (operands)
      rtx *operands ATTRIBUTE_UNUSED;
{
  rtx _val = 0;
  start_sequence ();

{
  rtx low  = m68hc11_gen_lowpart (SImode, operands[0]);
  rtx low2 = m68hc11_gen_lowpart (HImode, low);
  rtx src  = operands[1];


   if (!H_REG_P (src))
     {
       src = gen_rtx (REG, QImode, REGNO (operands[2]));
       emit_move_insn (src, operands[1]);
     }

   emit_move_insn (m68hc11_gen_lowpart (QImode, low2), src);
   emit_move_insn (operands[2], const0_rtx);
   src = gen_rtx (REG, QImode, REGNO (operands[2]));
   emit_move_insn (m68hc11_gen_highpart (QImode, low2), src);

   emit_move_insn (m68hc11_gen_highpart (HImode, low), operands[2]);
   low = m68hc11_gen_highpart (SImode, operands[0]);
   emit_move_insn (m68hc11_gen_lowpart (HImode, low), operands[2]);
   emit_move_insn (m68hc11_gen_highpart (HImode, low), operands[2]);
   DONE;
}
  emit_insn (const0_rtx);
  _val = get_insns ();
  end_sequence ();
  return _val;
}
