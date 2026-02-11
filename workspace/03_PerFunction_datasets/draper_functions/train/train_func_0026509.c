prism2_ioctl_siwrate(struct net_device *dev,
				struct iw_request_info *info,
				struct iw_param *rrq, char *extra)
{
	struct hostap_interface *iface;
	local_info_t *local;

	iface = netdev_priv(dev);
	local = iface->local;

	if (rrq->fixed) {
		switch (rrq->value) {
		case 11000000:
			local->tx_rate_control = HFA384X_RATES_11MBPS;
			break;
		case 5500000:
			local->tx_rate_control = HFA384X_RATES_5MBPS;
			break;
		case 2000000:
			local->tx_rate_control = HFA384X_RATES_2MBPS;
			break;
		case 1000000:
			local->tx_rate_control = HFA384X_RATES_1MBPS;
			break;
		default:
			local->tx_rate_control = HFA384X_RATES_1MBPS |
				HFA384X_RATES_2MBPS | HFA384X_RATES_5MBPS |
				HFA384X_RATES_11MBPS;
			break;
		}
	} else {
		switch (rrq->value) {
		case 11000000:
			local->tx_rate_control = HFA384X_RATES_1MBPS |
				HFA384X_RATES_2MBPS | HFA384X_RATES_5MBPS |
				HFA384X_RATES_11MBPS;
			break;
		case 5500000:
			local->tx_rate_control = HFA384X_RATES_1MBPS |
				HFA384X_RATES_2MBPS | HFA384X_RATES_5MBPS;
			break;
		case 2000000:
			local->tx_rate_control = HFA384X_RATES_1MBPS |
				HFA384X_RATES_2MBPS;
			break;
		case 1000000:
			local->tx_rate_control = HFA384X_RATES_1MBPS;
			break;
		default:
			local->tx_rate_control = HFA384X_RATES_1MBPS |
				HFA384X_RATES_2MBPS | HFA384X_RATES_5MBPS |
				HFA384X_RATES_11MBPS;
			break;
		}
	}

	return hostap_set_rate(dev);
}
