xpnet_dev_hard_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct xpnet_pending_msg *queued_msg;
	u64 start_addr, end_addr;
	short dest_partid;
	u16 embedded_bytes = 0;

	dev_dbg(xpnet, ">skb->head=0x%p skb->data=0x%p skb->tail=0x%p "
		"skb->end=0x%p skb->len=%d\n", (void *)skb->head,
		(void *)skb->data, skb_tail_pointer(skb), skb_end_pointer(skb),
		skb->len);

	if (skb->data[0] == 0x33) {
		dev_kfree_skb(skb);
		return NETDEV_TX_OK;
	}


	queued_msg = kmalloc(sizeof(struct xpnet_pending_msg), GFP_ATOMIC);
	if (queued_msg == NULL) {
		dev_warn(xpnet, "failed to kmalloc %ld bytes; dropping "
			 "packet\n", sizeof(struct xpnet_pending_msg));

		dev->stats.tx_errors++;
		dev_kfree_skb(skb);
		return NETDEV_TX_OK;
	}


	start_addr = ((u64)skb->data & ~(L1_CACHE_BYTES - 1));
	end_addr = L1_CACHE_ALIGN((u64)skb_tail_pointer(skb));


	if (unlikely(skb->len <= XPNET_MSG_DATA_MAX)) {

		embedded_bytes = skb->len;
	}


	atomic_set(&queued_msg->use_count, 1);
	queued_msg->skb = skb;

	if (skb->data[0] == 0xff) {

		for_each_set_bit(dest_partid, xpnet_broadcast_partitions,
			     xp_max_npartitions) {

			xpnet_send(skb, queued_msg, start_addr, end_addr,
				   embedded_bytes, dest_partid);
		}
	} else {
		dest_partid = (short)skb->data[XPNET_PARTID_OCTET + 1];
		dest_partid |= (short)skb->data[XPNET_PARTID_OCTET + 0] << 8;

		if (dest_partid >= 0 &&
		    dest_partid < xp_max_npartitions &&
		    test_bit(dest_partid, xpnet_broadcast_partitions) != 0) {

			xpnet_send(skb, queued_msg, start_addr, end_addr,
				   embedded_bytes, dest_partid);
		}
	}

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	if (atomic_dec_return(&queued_msg->use_count) == 0) {
		dev_kfree_skb(skb);
		kfree(queued_msg);
	}

	return NETDEV_TX_OK;
}
