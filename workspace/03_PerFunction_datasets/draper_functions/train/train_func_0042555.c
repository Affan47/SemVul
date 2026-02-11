efx_update_sw_stats(struct efx_nic *efx, u64 *stats)
{
	u64 n_rx_nodesc_trunc = 0;
	struct efx_channel *channel;

	efx_for_each_channel(channel, efx)
		n_rx_nodesc_trunc += channel->n_rx_nodesc_trunc;
	stats[GENERIC_STAT_rx_nodesc_trunc] = n_rx_nodesc_trunc;
	stats[GENERIC_STAT_rx_noskb_drops] = atomic_read(&efx->n_rx_noskb_drops);
}
