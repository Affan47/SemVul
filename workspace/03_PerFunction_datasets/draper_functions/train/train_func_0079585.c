mwifiex_init_channel_scan_gap(struct mwifiex_adapter *adapter)
{
	u32 n_channels_bg, n_channels_a = 0;

	n_channels_bg = mwifiex_band_2ghz.n_channels;

	if (adapter->config_bands & BAND_A)
		n_channels_a = mwifiex_band_5ghz.n_channels;

	adapter->num_in_chan_stats = n_channels_bg + n_channels_a;
	adapter->chan_stats = vmalloc(sizeof(*adapter->chan_stats) *
				      adapter->num_in_chan_stats);

	if (!adapter->chan_stats)
		return -ENOMEM;

	return 0;
}
