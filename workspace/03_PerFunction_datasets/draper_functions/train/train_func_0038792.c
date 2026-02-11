e1000_set_spd_dplx(struct e1000_adapter *adapter, u32 spd, u8 dplx)
{
	struct e1000_mac_info *mac = &adapter->hw.mac;

	mac->autoneg = 0;


	if ((spd & 1) || (dplx & ~1))
		goto err_inval;


	if ((adapter->hw.phy.media_type == e1000_media_type_fiber) &&
	    (spd != SPEED_1000) && (dplx != DUPLEX_FULL)) {
		goto err_inval;
	}

	switch (spd + dplx) {
	case SPEED_10 + DUPLEX_HALF:
		mac->forced_speed_duplex = ADVERTISE_10_HALF;
		break;
	case SPEED_10 + DUPLEX_FULL:
		mac->forced_speed_duplex = ADVERTISE_10_FULL;
		break;
	case SPEED_100 + DUPLEX_HALF:
		mac->forced_speed_duplex = ADVERTISE_100_HALF;
		break;
	case SPEED_100 + DUPLEX_FULL:
		mac->forced_speed_duplex = ADVERTISE_100_FULL;
		break;
	case SPEED_1000 + DUPLEX_FULL:
		mac->autoneg = 1;
		adapter->hw.phy.autoneg_advertised = ADVERTISE_1000_FULL;
		break;
	case SPEED_1000 + DUPLEX_HALF:
	default:
		goto err_inval;
	}


	adapter->hw.phy.mdix = AUTO_ALL_MODES;

	return 0;

err_inval:
	e_err("Unsupported Speed/Duplex configuration\n");
	return -EINVAL;
}
