ns83820_set_multicast(struct net_device *ndev)
{
	struct ns83820 *dev = PRIV(ndev);
	u8 __iomem *rfcr = dev->base + RFCR;
	u32 and_mask = 0xffffffff;
	u32 or_mask = 0;
	u32 val;

	if (ndev->flags & IFF_PROMISC)
		or_mask |= RFCR_AAU | RFCR_AAM;
	else
		and_mask &= ~(RFCR_AAU | RFCR_AAM);

	if (ndev->flags & IFF_ALLMULTI || netdev_mc_count(ndev))
		or_mask |= RFCR_AAM;
	else
		and_mask &= ~RFCR_AAM;

	spin_lock_irq(&dev->misc_lock);
	val = (readl(rfcr) & and_mask) | or_mask;

	writel(val & ~RFCR_RFEN, rfcr);
	writel(val, rfcr);
	spin_unlock_irq(&dev->misc_lock);
}
