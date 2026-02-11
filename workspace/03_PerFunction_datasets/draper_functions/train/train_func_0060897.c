sds_wr(void __iomem *csr_base, u32 indirect_cmd_reg,
		   u32 indirect_data_reg, u32 addr, u32 data)
{
	unsigned long deadline = jiffies + HZ;
	u32 val;
	u32 cmd;

	cmd = CFG_IND_WR_CMD_MASK | CFG_IND_CMD_DONE_MASK;
	cmd = CFG_IND_ADDR_SET(cmd, addr);
	writel(data, csr_base + indirect_data_reg);
	readl(csr_base + indirect_data_reg);
	writel(cmd, csr_base + indirect_cmd_reg);
	readl(csr_base + indirect_cmd_reg);
	do {
		val = readl(csr_base + indirect_cmd_reg);
	} while (!(val & CFG_IND_CMD_DONE_MASK) &&
		 time_before(jiffies, deadline));
	if (!(val & CFG_IND_CMD_DONE_MASK))
		pr_err("SDS WR timeout at 0x%p offset 0x%08X value 0x%08X\n",
		       csr_base + indirect_cmd_reg, addr, data);
}
