show_bssinfo(struct device *d, struct device_attribute *attr,
			    char *buf)
{
	struct ipw2100_priv *priv = dev_get_drvdata(d);
	char essid[IW_ESSID_MAX_SIZE + 1];
	u8 bssid[ETH_ALEN];
	u32 chan = 0;
	char *out = buf;
	unsigned int length;
	int ret;

	if (priv->status & STATUS_RF_KILL_MASK)
		return 0;

	memset(essid, 0, sizeof(essid));
	memset(bssid, 0, sizeof(bssid));

	length = IW_ESSID_MAX_SIZE;
	ret = ipw2100_get_ordinal(priv, IPW_ORD_STAT_ASSN_SSID, essid, &length);
	if (ret)
		IPW_DEBUG_INFO("failed querying ordinals at line %d\n",
			       __LINE__);

	length = sizeof(bssid);
	ret = ipw2100_get_ordinal(priv, IPW_ORD_STAT_ASSN_AP_BSSID,
				  bssid, &length);
	if (ret)
		IPW_DEBUG_INFO("failed querying ordinals at line %d\n",
			       __LINE__);

	length = sizeof(u32);
	ret = ipw2100_get_ordinal(priv, IPW_ORD_OUR_FREQ, &chan, &length);
	if (ret)
		IPW_DEBUG_INFO("failed querying ordinals at line %d\n",
			       __LINE__);

	out += sprintf(out, "ESSID: %s\n", essid);
	out += sprintf(out, "BSSID:   %pM\n", bssid);
	out += sprintf(out, "Channel: %d\n", chan);

	return out - buf;
}
