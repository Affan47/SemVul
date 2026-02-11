__tg3_set_rx_mode(struct net_device *dev)
{	DBGP("%s\n", __func__);

	struct tg3 *tp = netdev_priv(dev);
	u32 rx_mode;

	rx_mode = tp->rx_mode & ~(RX_MODE_PROMISC |
				  RX_MODE_KEEP_VLAN_TAG);

	rx_mode |= RX_MODE_KEEP_VLAN_TAG;


	tw32(MAC_HASH_REG_0, 0xffffffff);
	tw32(MAC_HASH_REG_1, 0xffffffff);
	tw32(MAC_HASH_REG_2, 0xffffffff);
	tw32(MAC_HASH_REG_3, 0xffffffff);

	if (rx_mode != tp->rx_mode) {
		tp->rx_mode = rx_mode;
		tw32_f(MAC_RX_MODE, rx_mode);
		udelay(10);
	}
}
