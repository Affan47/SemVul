put_reg(long i, uint32_t val)
{
	if (i == 6)
		mem_put(REGS16_R(gbcpu_regs, HL), val);
	else REGS8_W(gbcpu_regs, i, val);
}
