wlc_lcnphy_clear_tx_power_offsets(struct brcms_phy *pi)
{
	u32 data_buf[64];
	struct phytbl_info tab;

	memset(data_buf, 0, sizeof(data_buf));

	tab.tbl_id = LCNPHY_TBL_ID_TXPWRCTL;
	tab.tbl_width = 32;
	tab.tbl_ptr = data_buf;

	if (!wlc_lcnphy_tempsense_based_pwr_ctrl_enabled(pi)) {

		tab.tbl_len = 30;
		tab.tbl_offset = LCNPHY_TX_PWR_CTRL_RATE_OFFSET;
		wlc_lcnphy_write_table(pi, &tab);
	}

	tab.tbl_len = 64;
	tab.tbl_offset = LCNPHY_TX_PWR_CTRL_MAC_OFFSET;
	wlc_lcnphy_write_table(pi, &tab);
}
