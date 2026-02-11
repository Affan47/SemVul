rxd_owner_bit_reset(struct s2io_nic *sp)
{
	int i, j, k, blk_cnt = 0, size;
	struct config_param *config = &sp->config;
	struct mac_info *mac_control = &sp->mac_control;
	struct net_device *dev = sp->dev;
	struct RxD_t *rxdp = NULL;
	struct sk_buff *skb = NULL;
	struct buffAdd *ba = NULL;
	u64 temp0_64 = 0, temp1_64 = 0, temp2_64 = 0;


	size = dev->mtu + HEADER_ETHERNET_II_802_3_SIZE +
		HEADER_802_2_SIZE + HEADER_SNAP_SIZE;
	if (sp->rxd_mode == RXD_MODE_1)
		size += NET_IP_ALIGN;
	else if (sp->rxd_mode == RXD_MODE_3B)
		size = dev->mtu + ALIGN_SIZE + BUF0_LEN + 4;

	for (i = 0; i < config->rx_ring_num; i++) {
		struct rx_ring_config *rx_cfg = &config->rx_cfg[i];
		struct ring_info *ring = &mac_control->rings[i];

		blk_cnt = rx_cfg->num_rxd / (rxd_count[sp->rxd_mode] + 1);

		for (j = 0; j < blk_cnt; j++) {
			for (k = 0; k < rxd_count[sp->rxd_mode]; k++) {
				rxdp = ring->rx_blocks[j].rxds[k].virt_addr;
				if (sp->rxd_mode == RXD_MODE_3B)
					ba = &ring->ba[j][k];
				if (set_rxd_buffer_pointer(sp, rxdp, ba, &skb,
							   &temp0_64,
							   &temp1_64,
							   &temp2_64,
							   size) == -ENOMEM) {
					return 0;
				}

				set_rxd_buffer_size(sp, rxdp, size);
				dma_wmb();

				rxdp->Control_1 |= RXD_OWN_XENA;
			}
		}
	}
	return 0;

}
