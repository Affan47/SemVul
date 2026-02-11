step_time_from_reg(u8 reg, u8 mode)
{
	return mode ? 100 * reg : 400 * reg;
}
