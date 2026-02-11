falcon_stats_request(struct efx_nic *efx)
{
	struct falcon_nic_data *nic_data = efx->nic_data;
	efx_oword_t reg;

	WARN_ON(nic_data->stats_pending);
	WARN_ON(nic_data->stats_disable_count);

	FALCON_XMAC_STATS_DMA_FLAG(efx) = 0;
	nic_data->stats_pending = true;
	wmb();


	EFX_POPULATE_OWORD_2(reg,
			     FRF_AB_MAC_STAT_DMA_CMD, 1,
			     FRF_AB_MAC_STAT_DMA_ADR,
			     efx->stats_buffer.dma_addr);
	efx_writeo(efx, &reg, FR_AB_MAC_STAT_DMA);

	mod_timer(&nic_data->stats_timer, round_jiffies_up(jiffies + HZ / 2));
}
