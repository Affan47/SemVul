tg3_transmit(struct nic *nic, const char *dst_addr,
	unsigned int type, unsigned int size, const char *packet)
{
	static int frame_idx;
	struct eth_frame *frame;


	struct tg3_tx_buffer_desc *txd;
	struct tg3 *tp;
	uint32_t entry;
	int i;


	tp = &tg3;
	i = 0;
	entry = tp->tx_prod;
	while((tp->hw_status->idx[0].tx_consumer != entry) &&
		(tp->hw_status->idx[0].tx_consumer != PREV_TX(entry))) {
		mdelay(10);
		if (++i > 500) {
			printf("transmit timed out\n");
			tg3_halt(tp);
			tg3_setup_hw(tp);
			return;
		}
	}
	if (i != 0) {
		printf("#");
	}


	frame = &tg3_bss.tx_frame[frame_idx];
	memcpy(frame->dst_addr, dst_addr, ETH_ALEN);
	memcpy(frame->src_addr, nic->node_addr, ETH_ALEN);
	frame->type = htons(type);
	memset(frame->data, 0, sizeof(frame->data));
	memcpy(frame->data, packet, size);


	txd            = &tp->tx_ring[entry];
	txd->addr_hi   = 0;
	txd->addr_lo   = virt_to_bus(frame);
	txd->len_flags = ((size + ETH_HLEN) << TXD_LEN_SHIFT) | TXD_FLAG_END;
	txd->vlan_tag  = 0 << TXD_VLAN_TAG_SHIFT;


	entry = NEXT_TX(entry);
	frame_idx ^= 1;


	tw32_mailbox((MAILBOX_SNDHOST_PROD_IDX_0 + TG3_64BIT_REG_LOW), entry);
	tw32_mailbox2((MAILBOX_SNDHOST_PROD_IDX_0 + TG3_64BIT_REG_LOW), entry);
	tp->tx_prod = entry;
}
