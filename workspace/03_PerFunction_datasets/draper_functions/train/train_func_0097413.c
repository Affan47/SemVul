atl1e_clean_rx_irq(struct atl1e_adapter *adapter)
{
	struct net_device *netdev  = adapter->netdev;
	struct atl1e_rx_ring *rx_ring = (struct atl1e_rx_ring *)
					 &adapter->rx_ring;
	struct atl1e_rx_page_desc *rx_page_desc =
		(struct atl1e_rx_page_desc *) &rx_ring->rx_page_desc;
	struct io_buffer *iob = NULL;
	struct atl1e_rx_page *rx_page = atl1e_get_rx_page(adapter);
	u32 packet_size, write_offset;
	struct atl1e_recv_ret_status *prrs;

	write_offset = *(rx_page->write_offset_addr);
	if (rx_page->read_offset >= write_offset)
		return;

	do {

		prrs = (struct atl1e_recv_ret_status *) (rx_page->addr +
							 rx_page->read_offset);

		if (prrs->seq_num != rx_page_desc->rx_nxseq) {
			DBG("atl1e %s: RX sequence number error (%d != %d)\n",
			    netdev->name, prrs->seq_num,
			    rx_page_desc->rx_nxseq);
			rx_page_desc->rx_nxseq++;
			goto fatal_err;
		}

		rx_page_desc->rx_nxseq++;


		if (prrs->pkt_flag & RRS_IS_ERR_FRAME) {
			if (prrs->err_flag & (RRS_ERR_BAD_CRC |
					      RRS_ERR_DRIBBLE | RRS_ERR_CODE |
					      RRS_ERR_TRUNC)) {


				netdev_rx_err(netdev, NULL, EIO);
				goto skip_pkt;
			}
		}

		packet_size = ((prrs->word1 >> RRS_PKT_SIZE_SHIFT) &
			       RRS_PKT_SIZE_MASK) - ETH_FCS_LEN;
		iob = alloc_iob(packet_size + NET_IP_ALIGN);
		if (iob == NULL) {
			DBG("atl1e %s: dropping packet under memory pressure\n",
			    netdev->name);
			goto skip_pkt;
		}
		iob_reserve(iob, NET_IP_ALIGN);
		memcpy(iob->data, (u8 *)(prrs + 1), packet_size);
		iob_put(iob, packet_size);

		netdev_rx(netdev, iob);

skip_pkt:

		rx_page->read_offset +=
			(((u32)((prrs->word1 >> RRS_PKT_SIZE_SHIFT) &
				RRS_PKT_SIZE_MASK) +
			  sizeof(struct atl1e_recv_ret_status) + 31) &
			 0xFFFFFFE0);

		if (rx_page->read_offset >= rx_ring->page_size) {

			u16 reg_addr;
			u8  rx_using;

			rx_page->read_offset =
				*(rx_page->write_offset_addr) = 0;
			rx_using = rx_page_desc->rx_using;
			reg_addr =
				atl1e_rx_page_vld_regs[rx_using];
			AT_WRITE_REGB(&adapter->hw, reg_addr, 1);
			rx_page_desc->rx_using ^= 1;
			rx_page = atl1e_get_rx_page(adapter);
		}
		write_offset = *(rx_page->write_offset_addr);
	} while (rx_page->read_offset < write_offset);

	return;

fatal_err:
	if (!netdev_link_ok(adapter->netdev))
		atl1e_reset(adapter);
}
