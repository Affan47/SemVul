is_same_network(struct libipw_network *src,
				  struct libipw_network *dst)
{


	return ((src->ssid_len == dst->ssid_len) &&
		(src->channel == dst->channel) &&
		ether_addr_equal_64bits(src->bssid, dst->bssid) &&
		!memcmp(src->ssid, dst->ssid, src->ssid_len));
}
