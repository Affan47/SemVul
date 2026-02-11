xgbe_isr(int irq, void *data)
{
	struct xgbe_prv_data *pdata = data;
	struct xgbe_hw_if *hw_if = &pdata->hw_if;
	struct xgbe_channel *channel;
	unsigned int dma_isr, dma_ch_isr;
	unsigned int mac_isr, mac_tssr;
	unsigned int i;


	dma_isr = XGMAC_IOREAD(pdata, DMA_ISR);
	if (!dma_isr)
		goto isr_done;

	netif_dbg(pdata, intr, pdata->netdev, "DMA_ISR=%#010x\n", dma_isr);

	for (i = 0; i < pdata->channel_count; i++) {
		if (!(dma_isr & (1 << i)))
			continue;

		channel = pdata->channel + i;

		dma_ch_isr = XGMAC_DMA_IOREAD(channel, DMA_CH_SR);
		netif_dbg(pdata, intr, pdata->netdev, "DMA_CH%u_ISR=%#010x\n",
			  i, dma_ch_isr);


		if (!pdata->per_channel_irq &&
		    (XGMAC_GET_BITS(dma_ch_isr, DMA_CH_SR, TI) ||
		     XGMAC_GET_BITS(dma_ch_isr, DMA_CH_SR, RI))) {
			if (napi_schedule_prep(&pdata->napi)) {

				xgbe_disable_rx_tx_ints(pdata);


				__napi_schedule(&pdata->napi);
			}
		}

		if (XGMAC_GET_BITS(dma_ch_isr, DMA_CH_SR, RBU))
			pdata->ext_stats.rx_buffer_unavailable++;


		if (XGMAC_GET_BITS(dma_ch_isr, DMA_CH_SR, FBE))
			schedule_work(&pdata->restart_work);


		XGMAC_DMA_IOWRITE(channel, DMA_CH_SR, dma_ch_isr);
	}

	if (XGMAC_GET_BITS(dma_isr, DMA_ISR, MACIS)) {
		mac_isr = XGMAC_IOREAD(pdata, MAC_ISR);

		if (XGMAC_GET_BITS(mac_isr, MAC_ISR, MMCTXIS))
			hw_if->tx_mmc_int(pdata);

		if (XGMAC_GET_BITS(mac_isr, MAC_ISR, MMCRXIS))
			hw_if->rx_mmc_int(pdata);

		if (XGMAC_GET_BITS(mac_isr, MAC_ISR, TSIS)) {
			mac_tssr = XGMAC_IOREAD(pdata, MAC_TSSR);

			if (XGMAC_GET_BITS(mac_tssr, MAC_TSSR, TXTSC)) {

				pdata->tx_tstamp =
					hw_if->get_tx_tstamp(pdata);
				queue_work(pdata->dev_workqueue,
					   &pdata->tx_tstamp_work);
			}
		}
	}

isr_done:
	return IRQ_HANDLED;
}
