igb_get_pcs_speed_and_duplex_82575(struct e1000_hw *hw, u16 *speed,
						u16 *duplex)
{
	struct e1000_mac_info *mac = &hw->mac;
	u32 pcs, status;


	mac->serdes_has_link = false;
	*speed = 0;
	*duplex = 0;


	pcs = rd32(E1000_PCS_LSTAT);


	if ((pcs & E1000_PCS_LSTS_LINK_OK) && (pcs & E1000_PCS_LSTS_SYNK_OK)) {
		mac->serdes_has_link = true;


		if (pcs & E1000_PCS_LSTS_SPEED_1000)
			*speed = SPEED_1000;
		else if (pcs & E1000_PCS_LSTS_SPEED_100)
			*speed = SPEED_100;
		else
			*speed = SPEED_10;


		if (pcs & E1000_PCS_LSTS_DUPLEX_FULL)
			*duplex = FULL_DUPLEX;
		else
			*duplex = HALF_DUPLEX;


		if (mac->type == e1000_i354) {
			status = rd32(E1000_STATUS);
			if ((status & E1000_STATUS_2P5_SKU) &&
			    !(status & E1000_STATUS_2P5_SKU_OVER)) {
				*speed = SPEED_2500;
				*duplex = FULL_DUPLEX;
				hw_dbg("2500 Mbs, ");
				hw_dbg("Full Duplex\n");
			}
		}

	}

	return 0;
}
