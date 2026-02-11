wl3501_get_txpow(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	u16 txpow;
	struct wl3501_card *this = netdev_priv(dev);
	int rc = wl3501_get_mib_value(this,
				      WL3501_MIB_ATTR_CURRENT_TX_PWR_LEVEL,
				      &txpow, sizeof(txpow));
	if (!rc) {
		wrqu->txpower.value = txpow;
		wrqu->txpower.disabled = 0;


		wrqu->txpower.fixed = 0;
		wrqu->txpower.flags = IW_TXPOW_MWATT;
	}
	return rc;
}
