ax88179_set_multicast(struct net_device *net)
{
	struct usbnet *dev = netdev_priv(net);
	struct ax88179_data *data = (struct ax88179_data *)dev->data;
	u8 *m_filter = ((u8 *)dev->data) + 12;

	data->rxctl = (AX_RX_CTL_START | AX_RX_CTL_AB | AX_RX_CTL_IPE);

	if (net->flags & IFF_PROMISC) {
		data->rxctl |= AX_RX_CTL_PRO;
	} else if (net->flags & IFF_ALLMULTI ||
		   netdev_mc_count(net) > AX_MAX_MCAST) {
		data->rxctl |= AX_RX_CTL_AMALL;
	} else if (netdev_mc_empty(net)) {

	} else {


		u32 crc_bits;
		struct netdev_hw_addr *ha;

		memset(m_filter, 0, AX_MCAST_FLTSIZE);

		netdev_for_each_mc_addr(ha, net) {
			crc_bits = ether_crc(ETH_ALEN, ha->addr) >> 26;
			*(m_filter + (crc_bits >> 3)) |= (1 << (crc_bits & 7));
		}

		ax88179_write_cmd_async(dev, AX_ACCESS_MAC, AX_MULFLTARY,
					AX_MCAST_FLTSIZE, AX_MCAST_FLTSIZE,
					m_filter);

		data->rxctl |= AX_RX_CTL_AM;
	}

	ax88179_write_cmd_async(dev, AX_ACCESS_MAC, AX_RX_CTL,
				2, 2, &data->rxctl);
}
