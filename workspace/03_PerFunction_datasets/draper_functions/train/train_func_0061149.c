efx_describe_per_queue_stats(struct efx_nic *efx, u8 *strings)
{
	size_t n_stats = 0;
	struct efx_channel *channel;

	efx_for_each_channel(channel, efx) {
		if (efx_channel_has_tx_queues(channel)) {
			n_stats++;
			if (strings != NULL) {
				snprintf(strings, ETH_GSTRING_LEN,
					 "tx-%u.tx_packets",
					 channel->tx_queue[0].queue /
					 EFX_TXQ_TYPES);

				strings += ETH_GSTRING_LEN;
			}
		}
	}
	efx_for_each_channel(channel, efx) {
		if (efx_channel_has_rx_queue(channel)) {
			n_stats++;
			if (strings != NULL) {
				snprintf(strings, ETH_GSTRING_LEN,
					 "rx-%d.rx_packets", channel->channel);
				strings += ETH_GSTRING_LEN;
			}
		}
	}
	return n_stats;
}
