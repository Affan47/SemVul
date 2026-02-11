connman_network_set_wifi_channel(struct connman_network *network,
						uint16_t channel)
{
	DBG("network %p wifi channel %d", network, channel);

	network->wifi.channel = channel;

	return 0;
}
