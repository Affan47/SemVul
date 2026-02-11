nv_legacybackoff_reseed(struct net_device *dev)
{
	u8 __iomem *base = get_hwbase(dev);
	u32 reg;
	u32 low;
	int tx_status = 0;

	reg = readl(base + NvRegSlotTime) & ~NVREG_SLOTTIME_MASK;
	get_random_bytes(&low, sizeof(low));
	reg |= low & NVREG_SLOTTIME_MASK;


	tx_status = readl(base + NvRegTransmitterControl) & NVREG_XMITCTL_START;
	if (tx_status)
		nv_stop_tx(dev);
	nv_stop_rx(dev);
	writel(reg, base + NvRegSlotTime);
	if (tx_status)
		nv_start_tx(dev);
	nv_start_rx(dev);
}
