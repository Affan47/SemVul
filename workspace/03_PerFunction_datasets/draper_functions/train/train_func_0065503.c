frmw_to_linux(struct wilc *wilc, u8 *buff, u32 size, u32 pkt_offset)
{

	unsigned int frame_len = 0;
	int stats;
	unsigned char *buff_to_send = NULL;
	struct sk_buff *skb;
	struct net_device *wilc_netdev;
	perInterface_wlan_t *nic;

	wilc_netdev = GetIfHandler(wilc, buff);
	if (wilc_netdev == NULL)
		return;

	buff += pkt_offset;
	nic = netdev_priv(wilc_netdev);

	if (size > 0) {

		frame_len = size;
		buff_to_send = buff;


		skb = dev_alloc_skb(frame_len);
		if (skb == NULL) {
			PRINT_ER("Low memory - packet droped\n");
			return;
		}

		if (wilc == NULL || wilc_netdev == NULL)
			PRINT_ER("wilc_netdev in wilc is NULL");
		skb->dev = wilc_netdev;

		if (skb->dev == NULL)
			PRINT_ER("skb->dev is NULL\n");


		memcpy(skb_put(skb, frame_len), buff_to_send, frame_len);


		skb->protocol = eth_type_trans(skb, wilc_netdev);

		nic->netstats.rx_packets++;
		nic->netstats.rx_bytes += frame_len;
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		stats = netif_rx(skb);
		PRINT_D(RX_DBG, "netif_rx ret value is: %d\n", stats);
	}
}
