xgbe_tx_start_xmit(struct xgbe_channel *channel,
			       struct xgbe_ring *ring)
{
	struct xgbe_prv_data *pdata = channel->pdata;
	struct xgbe_ring_data *rdata;


	wmb();


	rdata = XGBE_GET_DESC_DATA(ring, ring->cur);
	XGMAC_DMA_IOWRITE(channel, DMA_CH_TDTR_LO,
			  lower_32_bits(rdata->rdesc_dma));


	if (pdata->tx_usecs && !channel->tx_timer_active) {
		channel->tx_timer_active = 1;
		mod_timer(&channel->tx_timer,
			  jiffies + usecs_to_jiffies(pdata->tx_usecs));
	}

	ring->tx.xmit_more = 0;
}
