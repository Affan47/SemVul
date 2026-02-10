e1000_run_loopback_test(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct e1000_tx_ring *txdr = &adapter->test_tx_ring;
	struct e1000_rx_ring *rxdr = &adapter->test_rx_ring;
	struct pci_dev *pdev = adapter->pdev;
	int i, j, k, l, lc, good_cnt, ret_val = 0;
	unsigned long time;

	ew32(RDT, rxdr->count - 1);


	if (rxdr->count <= txdr->count)
		lc = ((txdr->count / 64) * 2) + 1;
	else
		lc = ((rxdr->count / 64) * 2) + 1;

	k = l = 0;
	for (j = 0; j <= lc; j++) {
		for (i = 0; i < 64; i++) {
			e1000_create_lbtest_frame(txdr->buffer_info[i].skb,
						  1024);
			dma_sync_single_for_device(&pdev->dev,
						   txdr->buffer_info[k].dma,
						   txdr->buffer_info[k].length,
						   DMA_TO_DEVICE);
			if (unlikely(++k == txdr->count))
				k = 0;
		}
		ew32(TDT, k);
		E1000_WRITE_FLUSH();
		msleep(200);
		time = jiffies;
		good_cnt = 0;
		do {
			dma_sync_single_for_cpu(&pdev->dev,
						rxdr->buffer_info[l].dma,
						E1000_RXBUFFER_2048,
						DMA_FROM_DEVICE);

			ret_val = e1000_check_lbtest_frame(
					rxdr->buffer_info[l].rxbuf.data +
					NET_SKB_PAD + NET_IP_ALIGN,
					1024);
			if (!ret_val)
				good_cnt++;
			if (unlikely(++l == rxdr->count))
				l = 0;


		} while (good_cnt < 64 && time_after(time + 20, jiffies));

		if (good_cnt != 64) {
			ret_val = 13;
			break;
		}
		if (time_after_eq(jiffies, time + 2)) {
			ret_val = 14;
			break;
		}
	}
	return ret_val;
}
