dp83640_hwtstamp(struct phy_device *phydev, struct ifreq *ifr)
{
	struct dp83640_private *dp83640 = phydev->priv;
	struct hwtstamp_config cfg;
	u16 txcfg0, rxcfg0;

	if (copy_from_user(&cfg, ifr->ifr_data, sizeof(cfg)))
		return -EFAULT;

	if (cfg.flags)
		return -EINVAL;

	if (cfg.tx_type < 0 || cfg.tx_type > HWTSTAMP_TX_ONESTEP_SYNC)
		return -ERANGE;

	dp83640->hwts_tx_en = cfg.tx_type;

	switch (cfg.rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		dp83640->hwts_rx_en = 0;
		dp83640->layer = 0;
		dp83640->version = 0;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		dp83640->hwts_rx_en = 1;
		dp83640->layer = PTP_CLASS_L4;
		dp83640->version = PTP_CLASS_V1;
		break;
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		dp83640->hwts_rx_en = 1;
		dp83640->layer = PTP_CLASS_L4;
		dp83640->version = PTP_CLASS_V2;
		break;
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
		dp83640->hwts_rx_en = 1;
		dp83640->layer = PTP_CLASS_L2;
		dp83640->version = PTP_CLASS_V2;
		break;
	case HWTSTAMP_FILTER_PTP_V2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		dp83640->hwts_rx_en = 1;
		dp83640->layer = PTP_CLASS_L4 | PTP_CLASS_L2;
		dp83640->version = PTP_CLASS_V2;
		break;
	default:
		return -ERANGE;
	}

	txcfg0 = (dp83640->version & TX_PTP_VER_MASK) << TX_PTP_VER_SHIFT;
	rxcfg0 = (dp83640->version & TX_PTP_VER_MASK) << TX_PTP_VER_SHIFT;

	if (dp83640->layer & PTP_CLASS_L2) {
		txcfg0 |= TX_L2_EN;
		rxcfg0 |= RX_L2_EN;
	}
	if (dp83640->layer & PTP_CLASS_L4) {
		txcfg0 |= TX_IPV6_EN | TX_IPV4_EN;
		rxcfg0 |= RX_IPV6_EN | RX_IPV4_EN;
	}

	if (dp83640->hwts_tx_en)
		txcfg0 |= TX_TS_EN;

	if (dp83640->hwts_tx_en == HWTSTAMP_TX_ONESTEP_SYNC)
		txcfg0 |= SYNC_1STEP | CHK_1STEP;

	if (dp83640->hwts_rx_en)
		rxcfg0 |= RX_TS_EN;

	mutex_lock(&dp83640->clock->extreg_lock);

	ext_write(0, phydev, PAGE5, PTP_TXCFG0, txcfg0);
	ext_write(0, phydev, PAGE5, PTP_RXCFG0, rxcfg0);

	mutex_unlock(&dp83640->clock->extreg_lock);

	return copy_to_user(ifr->ifr_data, &cfg, sizeof(cfg)) ? -EFAULT : 0;
}
