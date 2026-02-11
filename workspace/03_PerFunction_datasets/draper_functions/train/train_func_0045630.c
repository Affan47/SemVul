__get_agg_bandwidth(struct aggregator *aggregator)
{
	int nports = __agg_active_ports(aggregator);
	u32 bandwidth = 0;

	if (nports) {
		switch (__get_link_speed(aggregator->lag_ports)) {
		case AD_LINK_SPEED_1MBPS:
			bandwidth = nports;
			break;
		case AD_LINK_SPEED_10MBPS:
			bandwidth = nports * 10;
			break;
		case AD_LINK_SPEED_100MBPS:
			bandwidth = nports * 100;
			break;
		case AD_LINK_SPEED_1000MBPS:
			bandwidth = nports * 1000;
			break;
		case AD_LINK_SPEED_2500MBPS:
			bandwidth = nports * 2500;
			break;
		case AD_LINK_SPEED_5000MBPS:
			bandwidth = nports * 5000;
			break;
		case AD_LINK_SPEED_10000MBPS:
			bandwidth = nports * 10000;
			break;
		case AD_LINK_SPEED_20000MBPS:
			bandwidth = nports * 20000;
			break;
		case AD_LINK_SPEED_25000MBPS:
			bandwidth = nports * 25000;
			break;
		case AD_LINK_SPEED_40000MBPS:
			bandwidth = nports * 40000;
			break;
		case AD_LINK_SPEED_50000MBPS:
			bandwidth = nports * 50000;
			break;
		case AD_LINK_SPEED_56000MBPS:
			bandwidth = nports * 56000;
			break;
		case AD_LINK_SPEED_100000MBPS:
			bandwidth = nports * 100000;
			break;
		default:
			bandwidth = 0;
		}
	}
	return bandwidth;
}
