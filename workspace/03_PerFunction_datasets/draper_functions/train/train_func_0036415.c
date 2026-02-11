nv_mgmt_release_sema(struct net_device *dev)
{
	struct fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 tx_ctrl;

	if (np->driver_data & DEV_HAS_MGMT_UNIT) {
		if (np->mgmt_sema) {
			tx_ctrl = readl(base + NvRegTransmitterControl);
			tx_ctrl &= ~NVREG_XMITCTL_HOST_SEMA_ACQ;
			writel(tx_ctrl, base + NvRegTransmitterControl);
		}
	}
}
