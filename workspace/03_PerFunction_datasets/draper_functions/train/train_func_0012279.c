rndis_get_station(struct wiphy *wiphy, struct net_device *dev,
			     const u8 *mac, struct station_info *sinfo)
{
	struct rndis_wlan_private *priv = wiphy_priv(wiphy);
	struct usbnet *usbdev = priv->usbdev;

	if (!ether_addr_equal(priv->bssid, mac))
		return -ENOENT;

	rndis_fill_station_info(usbdev, sinfo);

	return 0;
}
