fan_from_reg(u16 reg)
{
	reg &= 0xfffc;
	if (reg == 0x0000 || reg == 0xfffc)
		return 0;
	return 5400000UL / reg;
}
