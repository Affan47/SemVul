arc_ps2_calc_addr(struct arc_ps2_data *arc_ps2,
						  int index, bool status)
{
	void __iomem *addr;

	addr = arc_ps2->addr + 4 + 4 * index;
	if (status)
		addr += ARC_PS2_PORTS * 4;

	return addr;
}
