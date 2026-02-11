pcf50633_read_block(struct pcf50633 *pcf, u8 reg,
					int nr_regs, u8 *data)
{
	int ret;

	ret = regmap_raw_read(pcf->regmap, reg, data, nr_regs);
	if (ret != 0)
		return ret;

	return nr_regs;
}
