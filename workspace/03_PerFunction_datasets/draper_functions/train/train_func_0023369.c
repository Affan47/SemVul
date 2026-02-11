ipw2100_wx_set_power(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	struct ipw2100_priv *priv = libipw_priv(dev);
	int err = 0;

	mutex_lock(&priv->action_mutex);
	if (!(priv->status & STATUS_INITIALIZED)) {
		err = -EIO;
		goto done;
	}

	if (wrqu->power.disabled) {
		priv->power_mode = IPW_POWER_LEVEL(priv->power_mode);
		err = ipw2100_set_power_mode(priv, IPW_POWER_MODE_CAM);
		IPW_DEBUG_WX("SET Power Management Mode -> off\n");
		goto done;
	}

	switch (wrqu->power.flags & IW_POWER_MODE) {
	case IW_POWER_ON:
	case IW_POWER_MODE:
	case IW_POWER_ALL_R:
		break;
	default:
		IPW_DEBUG_WX("SET PM Mode: %X not supported.\n",
			     wrqu->power.flags);
		err = -EOPNOTSUPP;
		goto done;
	}


	priv->power_mode = IPW_POWER_ENABLED | priv->power_mode;
	err = ipw2100_set_power_mode(priv, IPW_POWER_LEVEL(priv->power_mode));

	IPW_DEBUG_WX("SET Power Management Mode -> 0x%02X\n", priv->power_mode);

      done:
	mutex_unlock(&priv->action_mutex);
	return err;

}
