lbs_cfg_del_key(struct wiphy *wiphy, struct net_device *netdev,
			   u8 key_index, bool pairwise, const u8 *mac_addr)
{

	lbs_deb_enter(LBS_DEB_CFG80211);

	lbs_deb_assoc("del_key: key_idx %d, mac_addr %pM\n",
		      key_index, mac_addr);

#ifdef TODO
	struct lbs_private *priv = wiphy_priv(wiphy);


	if (key_index < 3 && priv->wep_key_len[key_index]) {
		priv->wep_key_len[key_index] = 0;
		lbs_set_wep_keys(priv);
	}
#endif

	return 0;
}
