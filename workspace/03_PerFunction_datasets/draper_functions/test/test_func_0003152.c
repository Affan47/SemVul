ipw_wx_set_powermode(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);
	int mode = *(int *)extra;
	int err;

	mutex_lock(&priv->mutex);
	if ((mode < 1) || (mode > IPW_POWER_LIMIT))
		mode = IPW_POWER_AC;

	if (IPW_POWER_LEVEL(priv->power_mode) != mode) {
		err = ipw_send_power_mode(priv, mode);
		if (err) {
			IPW_DEBUG_WX("failed setting power mode.\n");
			mutex_unlock(&priv->mutex);
			return err;
		}
		priv->power_mode = IPW_POWER_ENABLED | mode;
	}
	mutex_unlock(&priv->mutex);
	return 0;
}
