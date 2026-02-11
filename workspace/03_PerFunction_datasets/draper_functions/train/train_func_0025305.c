waitfor_idle(struct idt77252_dev *card)
{
	u32 stat;

	stat = readl(SAR_REG_STAT);
	while (stat & SAR_STAT_CMDBZ)
		stat = readl(SAR_REG_STAT);
}
