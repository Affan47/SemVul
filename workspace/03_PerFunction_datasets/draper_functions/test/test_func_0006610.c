emit_alu_imm_reg(struct buffer *buf, unsigned char opc_ext,
			     long imm, enum machine_reg reg)
{
	int opc;

	if (is_imm_8(imm))
		opc = 0x83;
	else
		opc = 0x81;

	emit(buf, opc);
	emit(buf, x86_encode_mod_rm(0x3, opc_ext, x86_encode_reg(reg)));
	emit_imm(buf, imm);
}
