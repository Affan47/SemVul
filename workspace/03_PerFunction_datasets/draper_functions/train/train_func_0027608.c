lbs_cfg_get_station(struct wiphy *wiphy, struct net_device *dev,
			       const u8 *mac, struct station_info *sinfo)
{
	struct lbs_private *priv = wiphy_priv(wiphy);
	s8 signal, noise;
	int ret;
	size_t i;

	lbs_deb_enter(LBS_DEB_CFG80211);

	sinfo->filled |= BIT(NL80211_STA_INFO_TX_BYTES) |
			 BIT(NL80211_STA_INFO_TX_PACKETS) |
			 BIT(NL80211_STA_INFO_RX_BYTES) |
			 BIT(NL80211_STA_INFO_RX_PACKETS);
	sinfo->tx_bytes = priv->dev->stats.tx_bytes;
	sinfo->tx_packets = priv->dev->stats.tx_packets;
	sinfo->rx_bytes = priv->dev->stats.rx_bytes;
	sinfo->rx_packets = priv->dev->stats.rx_packets;


	ret = lbs_get_rssi(priv, &signal, &noise);
	if (ret == 0) {
		sinfo->signal = signal;
		sinfo->filled |= BIT(NL80211_STA_INFO_SIGNAL);
	}


	for (i = 0; i < ARRAY_SIZE(lbs_rates); i++) {
		if (priv->cur_rate == lbs_rates[i].hw_value) {
			sinfo->txrate.legacy = lbs_rates[i].bitrate;
			sinfo->filled |= BIT(NL80211_STA_INFO_TX_BITRATE);
			break;
		}
	}

	return 0;
}
