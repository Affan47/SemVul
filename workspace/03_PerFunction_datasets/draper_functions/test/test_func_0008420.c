drc_append_standard_epilogue(struct drccore *drc, INT32 cycles, INT32 pcdelta, int allow_exit)
{
	if (cycles != 0)
		_sub_r32_imm(REG_EBP, cycles);
	if (pcdelta != 0)
		_lea_r32_m32bd(REG_EDI, REG_EDI, pcdelta);
	if (allow_exit && cycles != 0)
		_jcc(COND_S, drc->out_of_cycles);
}
