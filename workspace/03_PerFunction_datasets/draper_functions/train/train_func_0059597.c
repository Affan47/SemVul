emit_prolog(struct buffer *buf, unsigned long nr_locals)
{

	__emit_push_reg(buf, MACH_REG_EDI);
	__emit_push_reg(buf, MACH_REG_ESI);
	__emit_push_reg(buf, MACH_REG_EBX);

	__emit_push_reg(buf, MACH_REG_EBP);
	__emit_mov_reg_reg(buf, MACH_REG_ESP, MACH_REG_EBP);

	if (nr_locals)
		__emit_sub_imm_reg(buf, nr_locals * sizeof(unsigned long), MACH_REG_ESP);
}
