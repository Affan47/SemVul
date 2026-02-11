ixgbevf_xmit_frame(struct sk_buff *skb, struct net_device *netdev)
{
	struct ixgbevf_adapter *adapter = netdev_priv(netdev);
	struct ixgbevf_tx_buffer *first;
	struct ixgbevf_ring *tx_ring;
	int tso;
	u32 tx_flags = 0;
	u16 count = TXD_USE_COUNT(skb_headlen(skb));
#if PAGE_SIZE > IXGBE_MAX_DATA_PER_TXD
	unsigned short f;
#endif
	u8 hdr_len = 0;
	u8 *dst_mac = skb_header_pointer(skb, 0, 0, NULL);

	if (!dst_mac || is_link_local_ether_addr(dst_mac)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	tx_ring = adapter->tx_ring[skb->queue_mapping];


#if PAGE_SIZE > IXGBE_MAX_DATA_PER_TXD
	for (f = 0; f < skb_shinfo(skb)->nr_frags; f++)
		count += TXD_USE_COUNT(skb_shinfo(skb)->frags[f].size);
#else
	count += skb_shinfo(skb)->nr_frags;
#endif
	if (ixgbevf_maybe_stop_tx(tx_ring, count + 3)) {
		tx_ring->tx_stats.tx_busy++;
		return NETDEV_TX_BUSY;
	}


	first = &tx_ring->tx_buffer_info[tx_ring->next_to_use];
	first->skb = skb;
	first->bytecount = skb->len;
	first->gso_segs = 1;

	if (skb_vlan_tag_present(skb)) {
		tx_flags |= skb_vlan_tag_get(skb);
		tx_flags <<= IXGBE_TX_FLAGS_VLAN_SHIFT;
		tx_flags |= IXGBE_TX_FLAGS_VLAN;
	}


	first->tx_flags = tx_flags;
	first->protocol = vlan_get_protocol(skb);

	tso = ixgbevf_tso(tx_ring, first, &hdr_len);
	if (tso < 0)
		goto out_drop;
	else if (!tso)
		ixgbevf_tx_csum(tx_ring, first);

	ixgbevf_tx_map(tx_ring, first, hdr_len);

	ixgbevf_maybe_stop_tx(tx_ring, DESC_NEEDED);

	return NETDEV_TX_OK;

out_drop:
	dev_kfree_skb_any(first->skb);
	first->skb = NULL;

	return NETDEV_TX_OK;
}
