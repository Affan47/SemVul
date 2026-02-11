sis190_set_rx_mode(struct net_device *dev)
{
	struct sis190_private *tp = netdev_priv(dev);
	void __iomem *ioaddr = tp->mmio_addr;
	unsigned long flags;
	u32 mc_filter[2];
	u16 rx_mode;

	if (dev->flags & IFF_PROMISC) {
		rx_mode =
			AcceptBroadcast | AcceptMulticast | AcceptMyPhys |
			AcceptAllPhys;
		mc_filter[1] = mc_filter[0] = 0xffffffff;
	} else if ((netdev_mc_count(dev) > multicast_filter_limit) ||
		   (dev->flags & IFF_ALLMULTI)) {

		rx_mode = AcceptBroadcast | AcceptMulticast | AcceptMyPhys;
		mc_filter[1] = mc_filter[0] = 0xffffffff;
	} else {
		struct netdev_hw_addr *ha;

		rx_mode = AcceptBroadcast | AcceptMyPhys;
		mc_filter[1] = mc_filter[0] = 0;
		netdev_for_each_mc_addr(ha, dev) {
			int bit_nr =
				ether_crc(ETH_ALEN, ha->addr) & 0x3f;
			mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
			rx_mode |= AcceptMulticast;
		}
	}

	spin_lock_irqsave(&tp->lock, flags);

	SIS_W16(RxMacControl, rx_mode | 0x2);
	SIS_W32(RxHashTable, mc_filter[0]);
	SIS_W32(RxHashTable + 4, mc_filter[1]);

	spin_unlock_irqrestore(&tp->lock, flags);
}
