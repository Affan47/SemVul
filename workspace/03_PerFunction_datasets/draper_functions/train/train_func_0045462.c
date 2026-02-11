rndis_wlan_get_caps(struct usbnet *usbdev, struct wiphy *wiphy)
{
	struct {
		__le32	num_items;
		__le32	items[8];
	} networks_supported;
	struct ndis_80211_capability *caps;
	u8 caps_buf[sizeof(*caps) + sizeof(caps->auth_encr_pair) * 16];
	int len, retval, i, n;
	struct rndis_wlan_private *priv = get_rndis_wlan_priv(usbdev);


	len = sizeof(networks_supported);
	retval = rndis_query_oid(usbdev,
				 RNDIS_OID_802_11_NETWORK_TYPES_SUPPORTED,
				 &networks_supported, &len);
	if (retval >= 0) {
		n = le32_to_cpu(networks_supported.num_items);
		if (n > 8)
			n = 8;
		for (i = 0; i < n; i++) {
			switch (le32_to_cpu(networks_supported.items[i])) {
			case NDIS_80211_TYPE_FREQ_HOP:
			case NDIS_80211_TYPE_DIRECT_SEQ:
				priv->caps |= CAP_MODE_80211B;
				break;
			case NDIS_80211_TYPE_OFDM_A:
				priv->caps |= CAP_MODE_80211A;
				break;
			case NDIS_80211_TYPE_OFDM_G:
				priv->caps |= CAP_MODE_80211G;
				break;
			}
		}
	}


	caps = (struct ndis_80211_capability *)caps_buf;
	len = sizeof(caps_buf);
	retval = rndis_query_oid(usbdev,
				 RNDIS_OID_802_11_CAPABILITY,
				 caps, &len);
	if (retval >= 0) {
		netdev_dbg(usbdev->net, "RNDIS_OID_802_11_CAPABILITY -> len %d, "
				"ver %d, pmkids %d, auth-encr-pairs %d\n",
				le32_to_cpu(caps->length),
				le32_to_cpu(caps->version),
				le32_to_cpu(caps->num_pmkids),
				le32_to_cpu(caps->num_auth_encr_pair));
		wiphy->max_num_pmkids = le32_to_cpu(caps->num_pmkids);
	} else
		wiphy->max_num_pmkids = 0;

	return retval;
}
