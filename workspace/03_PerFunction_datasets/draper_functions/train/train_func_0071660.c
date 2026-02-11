ixgbe_rx_checksum(struct ixgbe_ring *ring,
				     union ixgbe_adv_rx_desc *rx_desc,
				     struct sk_buff *skb)
{
	__le16 pkt_info = rx_desc->wb.lower.lo_dword.hs_rss.pkt_info;
	__le16 hdr_info = rx_desc->wb.lower.lo_dword.hs_rss.hdr_info;
	bool encap_pkt = false;

	skb_checksum_none_assert(skb);


	if (!(ring->netdev->features & NETIF_F_RXCSUM))
		return;

	if ((pkt_info & cpu_to_le16(IXGBE_RXDADV_PKTTYPE_VXLAN)) &&
	    (hdr_info & cpu_to_le16(IXGBE_RXDADV_PKTTYPE_TUNNEL >> 16))) {
		encap_pkt = true;
		skb->encapsulation = 1;
	}


	if (ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_IPCS) &&
	    ixgbe_test_staterr(rx_desc, IXGBE_RXDADV_ERR_IPE)) {
		ring->rx_stats.csum_err++;
		return;
	}

	if (!ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_L4CS))
		return;

	if (ixgbe_test_staterr(rx_desc, IXGBE_RXDADV_ERR_TCPE)) {


		if ((pkt_info & cpu_to_le16(IXGBE_RXDADV_PKTTYPE_UDP)) &&
		    test_bit(__IXGBE_RX_CSUM_UDP_ZERO_ERR, &ring->state))
			return;

		ring->rx_stats.csum_err++;
		return;
	}


	skb->ip_summed = CHECKSUM_UNNECESSARY;
	if (encap_pkt) {
		if (!ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_OUTERIPCS))
			return;

		if (ixgbe_test_staterr(rx_desc, IXGBE_RXDADV_ERR_OUTERIPER)) {
			skb->ip_summed = CHECKSUM_NONE;
			return;
		}

		skb->csum_level = 1;
	}
}
