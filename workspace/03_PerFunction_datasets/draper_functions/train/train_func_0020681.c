emit3(
	struct radeon_compiler * c, struct rc_instruction * after,
	rc_opcode Opcode, struct rc_sub_instruction * base,
	struct rc_dst_register DstReg,
	struct rc_src_register SrcReg0, struct rc_src_register SrcReg1,
	struct rc_src_register SrcReg2)
{
	struct rc_instruction *fpi = rc_insert_new_instruction(c, after);

	if (base) {
		memcpy(&fpi->U.I, base, sizeof(struct rc_sub_instruction));
	}

	fpi->U.I.Opcode = Opcode;
	fpi->U.I.DstReg = DstReg;
	fpi->U.I.SrcReg[0] = SrcReg0;
	fpi->U.I.SrcReg[1] = SrcReg1;
	fpi->U.I.SrcReg[2] = SrcReg2;
	return fpi;
}
