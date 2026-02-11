megasas_clear_intr_fusion(struct megasas_register_set __iomem *regs)
{
	u32 status;


	status = readl(&regs->outbound_intr_status);

	if (status & 1) {
		writel(status, &regs->outbound_intr_status);
		readl(&regs->outbound_intr_status);
		return 1;
	}
	if (!(status & MFI_FUSION_ENABLE_INTERRUPT_MASK))
		return 0;

	return 1;
}
