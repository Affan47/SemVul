vlsi_unarm_rx(vlsi_irda_dev_t *idev)
{
	struct net_device *ndev = pci_get_drvdata(idev->pdev);
	struct vlsi_ring *r = idev->rx_ring;
	struct ring_descr *rd;
	int ret;

	for (rd = ring_first(r); rd != NULL; rd = ring_get(r)) {

		ret = 0;
		if (rd_is_active(rd)) {
			rd_set_status(rd, 0);
			if (rd_get_count(rd)) {
				pr_debug("%s - dropping rx packet\n", __func__);
				ret = -VLSI_RX_DROP;
			}
			rd_set_count(rd, 0);
			pci_dma_sync_single_for_cpu(r->pdev, rd_get_addr(rd), r->len, r->dir);
			if (rd->skb) {
				dev_kfree_skb_any(rd->skb);
				rd->skb = NULL;
			}
		}
		else
			ret = vlsi_process_rx(r, rd);

		if (ret < 0) {
			ret = -ret;
			ndev->stats.rx_errors++;
			if (ret & VLSI_RX_DROP)
				ndev->stats.rx_dropped++;
			if (ret & VLSI_RX_OVER)
				ndev->stats.rx_over_errors++;
			if (ret & VLSI_RX_LENGTH)
				ndev->stats.rx_length_errors++;
			if (ret & VLSI_RX_FRAME)
				ndev->stats.rx_frame_errors++;
			if (ret & VLSI_RX_CRC)
				ndev->stats.rx_crc_errors++;
		}
		else if (ret > 0) {
			ndev->stats.rx_packets++;
			ndev->stats.rx_bytes += ret;
		}
	}
}
