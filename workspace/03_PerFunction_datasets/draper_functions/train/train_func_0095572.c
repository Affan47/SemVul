get_reg(long i)
{
	if (i == 6)
		return mem_get(REGS16_R(gbcpu_regs, HL));
	return REGS8_R(gbcpu_regs, i);
}
