stb6100_write_reg(struct stb6100_state *state, u8 reg, u8 data)
{
	if (unlikely(reg >= STB6100_NUMREGS)) {
		dprintk(verbose, FE_ERROR, 1, "Invalid register offset 0x%x", reg);
		return -EREMOTEIO;
	}
	data = (data & stb6100_template[reg].mask) | stb6100_template[reg].set;
	return stb6100_write_reg_range(state, &data, reg, 1);
}
