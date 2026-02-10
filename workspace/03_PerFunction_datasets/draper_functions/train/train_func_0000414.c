dis_format(const struct msp430_instruction *insn)
{
	int len = 0;
	const char *opname = dis_opcode_name(insn->op);
	const char *suffix = "";

	if (!opname)
		opname = "???";

	if (insn->dsize == MSP430_DSIZE_BYTE)
		suffix = ".B";
	else if (insn->dsize == MSP430_DSIZE_AWORD)
		suffix = ".A";
	else if (insn->dsize == MSP430_DSIZE_UNKNOWN)
		suffix = ".?";


	if (insn->op == MSP430_OP_MOVA || insn->op == MSP430_OP_CMPA ||
	    insn->op == MSP430_OP_SUBA || insn->op == MSP430_OP_ADDA ||
	    insn->op == MSP430_OP_BRA || insn->op == MSP430_OP_RETA)
		suffix = "";

	len += printc("\x1b[36m%s%s\x1b[0m", opname, suffix);
	while (len < 8)
		len += printc(" ");


	if (insn->itype == MSP430_ITYPE_DOUBLE) {
		len += format_operand(insn->src_mode,
				      insn->src_addr,
				      insn->src_reg);

		printc(",");
		while (len < 15)
			len += printc(" ");
		printc(" ");
	}


	if (insn->itype != MSP430_ITYPE_NOARG)
		len += format_operand(insn->dst_mode,
					insn->dst_addr,
					insn->dst_reg);


	if (insn->rep_register)
		len += printc(" [repeat %s]", dis_reg_name(insn->rep_index));
	else if (insn->rep_index)
		len += printc(" [repeat %d]", insn->rep_index + 1);

	return len;
}
