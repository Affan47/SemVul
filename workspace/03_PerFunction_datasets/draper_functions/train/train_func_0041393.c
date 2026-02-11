fm10k_set_ts_config(struct net_device *netdev, struct ifreq *ifr)
{
	struct fm10k_intfc *interface = netdev_priv(netdev);
	struct hwtstamp_config ts_config;

	if (copy_from_user(&ts_config, ifr->ifr_data, sizeof(ts_config)))
		return -EFAULT;


	if (ts_config.flags)
		return -EINVAL;

	switch (ts_config.tx_type) {
	case HWTSTAMP_TX_OFF:
		break;
	case HWTSTAMP_TX_ON:

		break;
	default:
		return -ERANGE;
	}

	switch (ts_config.rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		interface->flags &= ~FM10K_FLAG_RX_TS_ENABLED;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	case HWTSTAMP_FILTER_ALL:
		interface->flags |= FM10K_FLAG_RX_TS_ENABLED;
		ts_config.rx_filter = HWTSTAMP_FILTER_ALL;
		break;
	default:
		return -ERANGE;
	}


	interface->ts_config = ts_config;

	return copy_to_user(ifr->ifr_data, &ts_config, sizeof(ts_config)) ?
		-EFAULT : 0;
}
