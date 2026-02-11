get_dimm_attr(u32 reg, int lobit, int hibit, int add, int minval,
			 int maxval, char *name)
{
	u32 val = GET_BITFIELD(reg, lobit, hibit);

	if (val < minval || val > maxval) {
		edac_dbg(2, "bad %s = %d (raw=%x)\n", name, val, reg);
		return -EINVAL;
	}
	return val + add;
}
