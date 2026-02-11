rd_reg16(struct slgt_info *info, unsigned int addr)
{
	CALC_REGADDR();
	return readw((void __iomem *)reg_addr);
}
