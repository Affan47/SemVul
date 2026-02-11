ahd_download_instr(struct ahd_softc *ahd, u_int instrptr, uint8_t *dconsts)
{
	union	ins_formats instr;
	struct	ins_format1 *fmt1_ins;
	struct	ins_format3 *fmt3_ins;
	u_int	opcode;


	instr.integer = ahd_le32toh(*(uint32_t*)&seqprog[instrptr * 4]);

	fmt1_ins = &instr.format1;
	fmt3_ins = NULL;


	opcode = instr.format1.opcode;
	switch (opcode) {
	case AIC_OP_JMP:
	case AIC_OP_JC:
	case AIC_OP_JNC:
	case AIC_OP_CALL:
	case AIC_OP_JNE:
	case AIC_OP_JNZ:
	case AIC_OP_JE:
	case AIC_OP_JZ:
	{
		fmt3_ins = &instr.format3;
		fmt3_ins->address = ahd_resolve_seqaddr(ahd, fmt3_ins->address);

	}
	case AIC_OP_OR:
	case AIC_OP_AND:
	case AIC_OP_XOR:
	case AIC_OP_ADD:
	case AIC_OP_ADC:
	case AIC_OP_BMOV:
		if (fmt1_ins->parity != 0) {
			fmt1_ins->immediate = dconsts[fmt1_ins->immediate];
		}
		fmt1_ins->parity = 0;

	case AIC_OP_ROL:
	{
		int i, count;


		for (i = 0, count = 0; i < 31; i++) {
			uint32_t mask;

			mask = 0x01 << i;
			if ((instr.integer & mask) != 0)
				count++;
		}
		if ((count & 0x01) == 0)
			instr.format1.parity = 1;


		instr.integer = ahd_htole32(instr.integer);
		ahd_outsb(ahd, SEQRAM, instr.bytes, 4);
		break;
	}
	default:
		panic("Unknown opcode encountered in seq program");
		break;
	}
}
