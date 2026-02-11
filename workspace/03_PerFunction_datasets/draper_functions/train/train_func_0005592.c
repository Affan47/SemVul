c2_activity(struct c2_dev *c2dev, u32 mq_index, u16 shared)
{


	while (readl(c2dev->regs + PCI_BAR0_ADAPTER_HINT) & 0x80000000)
		udelay(10);

	__raw_writel(C2_HINT_MAKE(mq_index, shared),
		     c2dev->regs + PCI_BAR0_ADAPTER_HINT);
}
