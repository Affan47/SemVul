tinsn_from_insnbuf (TInsn *tinsn,
		    xtensa_insnbuf slotbuf,
		    xtensa_format fmt,
		    int slot)
{
  int i;
  xtensa_isa isa = xtensa_default_isa;


  tinsn_init (tinsn);
  tinsn->insn_type = ITYPE_INSN;
  tinsn->is_specific_opcode = FALSE;
  tinsn->opcode = xtensa_opcode_decode (isa, fmt, slot, slotbuf);
  tinsn->ntok = xtensa_opcode_num_operands (isa, tinsn->opcode);
  for (i = 0; i < tinsn->ntok; i++)
    {
      set_expr_const (&tinsn->tok[i],
		      xtensa_insnbuf_get_operand (slotbuf, fmt, slot,
						  tinsn->opcode, i));
    }
}
