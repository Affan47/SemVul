ray_rx(struct net_device *dev, ray_dev_t *local,
		   struct rcs __iomem *prcs)
{
	int rx_len;
	unsigned int pkt_addr;
	void __iomem *pmsg;
	pr_debug("ray_rx process rx packet\n");


	pkt_addr = ((readb(&prcs->var.rx_packet.rx_data_ptr[0]) << 8)
		    + readb(&prcs->var.rx_packet.rx_data_ptr[1])) & RX_BUFF_END;

	rx_len = (readb(&prcs->var.rx_packet.rx_data_length[0]) << 8)
	    + readb(&prcs->var.rx_packet.rx_data_length[1]);

	local->last_rsl = readb(&prcs->var.rx_packet.rx_sig_lev);
	pmsg = local->rmem + pkt_addr;
	switch (readb(pmsg)) {
	case DATA_TYPE:
		pr_debug("ray_rx data type\n");
		rx_data(dev, prcs, pkt_addr, rx_len);
		break;
	case AUTHENTIC_TYPE:
		pr_debug("ray_rx authentic type\n");
		if (sniffer)
			rx_data(dev, prcs, pkt_addr, rx_len);
		else
			rx_authenticate(local, prcs, pkt_addr, rx_len);
		break;
	case DEAUTHENTIC_TYPE:
		pr_debug("ray_rx deauth type\n");
		if (sniffer)
			rx_data(dev, prcs, pkt_addr, rx_len);
		else
			rx_deauthenticate(local, prcs, pkt_addr, rx_len);
		break;
	case NULL_MSG_TYPE:
		pr_debug("ray_cs rx NULL msg\n");
		break;
	case BEACON_TYPE:
		pr_debug("ray_rx beacon type\n");
		if (sniffer)
			rx_data(dev, prcs, pkt_addr, rx_len);

		copy_from_rx_buff(local, (UCHAR *) &local->last_bcn, pkt_addr,
				  rx_len < sizeof(struct beacon_rx) ?
				  rx_len : sizeof(struct beacon_rx));

		local->beacon_rxed = 1;

		ray_get_stats(dev);
		break;
	default:
		pr_debug("ray_cs unknown pkt type %2x\n",
		      (unsigned int)readb(pmsg));
		break;
	}

}
