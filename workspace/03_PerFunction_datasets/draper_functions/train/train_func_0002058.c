__emit_lopc_memindex(struct buffer *buf,
				 int rex_w,
				 unsigned char *lopc,
				 size_t lopc_size,
				 unsigned char shift,
				 enum machine_reg index_reg,
				 enum machine_reg base_reg,
				 unsigned char reg_opcode)
{
	int needs_disp;
	unsigned char rex_pfx = 0, mod_rm, sib;
	unsigned char __index_reg = x86_encode_reg(index_reg);
	unsigned char __base_reg = x86_encode_reg(base_reg);

	needs_disp = (base_reg == MACH_REG_R13);

	if (needs_disp)
		mod_rm = x86_encode_mod_rm(0x01, reg_opcode, 0x04);
	else
		mod_rm = x86_encode_mod_rm(0x00, reg_opcode, 0x04);
	sib = x86_encode_sib(shift, __index_reg, __base_reg);

	if (rex_w)
		rex_pfx |= REX_W;
	if (reg_high(reg_opcode))
		rex_pfx |= REX_R;
	if (reg_high(__index_reg))
		rex_pfx |= REX_X;
	if (reg_high(__base_reg))
		rex_pfx |= REX_B;

	emit_lopc(buf, rex_pfx, lopc, lopc_size);
	emit(buf, mod_rm);
	emit(buf, sib);
	if (needs_disp)
		emit(buf, 0);
}
