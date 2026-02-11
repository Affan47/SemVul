imm_membase_insn(enum insn_type insn_type, unsigned long imm,
			      struct var_info *base_reg, long disp)
{
	struct insn *insn = alloc_insn(insn_type);

	if (insn) {
		insn->src	= (struct operand) {
			.type		= OPERAND_IMM,
			{
				.imm		= imm,
			}
		};
		init_membase_operand(insn, &insn->dest, base_reg, disp);
	}
	return insn;
}
