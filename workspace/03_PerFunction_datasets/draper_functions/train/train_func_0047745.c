uli526x_rx_packet(struct net_device *dev, struct uli526x_board_info * db)
{
	struct rx_desc *rxptr;
	struct sk_buff *skb;
	int rxlen;
	u32 rdes0;

	rxptr = db->rx_ready_ptr;

	while(db->rx_avail_cnt) {
		rdes0 = le32_to_cpu(rxptr->rdes0);
		if (rdes0 & 0x80000000)
		{
			break;
		}

		db->rx_avail_cnt--;
		db->interval_rx_cnt++;

		pci_unmap_single(db->pdev, le32_to_cpu(rxptr->rdes2), RX_ALLOC_SIZE, PCI_DMA_FROMDEVICE);
		if ( (rdes0 & 0x300) != 0x300) {


			ULI526X_DBUG(0, "Reuse SK buffer, rdes0", rdes0);
			uli526x_reuse_skb(db, rxptr->rx_skb_ptr);
		} else {

			rxlen = ( (rdes0 >> 16) & 0x3fff) - 4;


			if (rdes0 & 0x8000) {

				dev->stats.rx_errors++;
				if (rdes0 & 1)
					dev->stats.rx_fifo_errors++;
				if (rdes0 & 2)
					dev->stats.rx_crc_errors++;
				if (rdes0 & 0x80)
					dev->stats.rx_length_errors++;
			}

			if ( !(rdes0 & 0x8000) ||
				((db->cr6_data & CR6_PM) && (rxlen>6)) ) {
				struct sk_buff *new_skb = NULL;

				skb = rxptr->rx_skb_ptr;


				if ((rxlen < RX_COPY_SIZE) &&
				    (((new_skb = netdev_alloc_skb(dev, rxlen + 2)) != NULL))) {
					skb = new_skb;

					skb_reserve(skb, 2);
					memcpy(skb_put(skb, rxlen),
					       skb_tail_pointer(rxptr->rx_skb_ptr),
					       rxlen);
					uli526x_reuse_skb(db, rxptr->rx_skb_ptr);
				} else
					skb_put(skb, rxlen);

				skb->protocol = eth_type_trans(skb, dev);
				netif_rx(skb);
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += rxlen;

			} else {

				ULI526X_DBUG(0, "Reuse SK buffer, rdes0", rdes0);
				uli526x_reuse_skb(db, rxptr->rx_skb_ptr);
			}
		}

		rxptr = rxptr->next_rx_desc;
	}

	db->rx_ready_ptr = rxptr;
}
