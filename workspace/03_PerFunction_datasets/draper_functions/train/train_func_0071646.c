insn_uses_reg(struct insn *insn, struct use_position **regs)
{
	unsigned long flags;
	unsigned long nr = 0;

	flags = insn_flags[insn->type];

	if (insn_is_phi(insn)) {
		if (flags & USE_SRC) {
			for (unsigned long i = 0; i < insn->nr_srcs; i++)
				regs[nr++] = &insn->ssa_srcs[i].reg;
		}

		return nr;
	}

	if (flags & USE_SRC)
		regs[nr++] = &insn->src.reg;

	if (flags & USE_DST)
		regs[nr++] = &insn->dest.reg;

	if (flags & USE_IDX_SRC)
		regs[nr++] = &insn->src.index_reg;

	if (flags & USE_IDX_DST)
		regs[nr++] = &insn->dest.index_reg;

	return nr;
}
