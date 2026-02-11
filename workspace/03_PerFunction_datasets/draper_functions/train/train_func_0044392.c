atl1c_post_phy_linkchg(struct atl1c_hw *hw, u16 link_speed)
{
	u16 phy_val;
	bool adj_thresh = false;

	if (hw->nic_type == athr_l2c_b || hw->nic_type == athr_l2c_b2 ||
	    hw->nic_type == athr_l1d || hw->nic_type == athr_l1d_2)
		adj_thresh = true;

	if (link_speed != SPEED_0) {

		if (hw->nic_type == athr_l1d_2) {
			atl1c_read_phy_ext(hw, MIIEXT_PCS, MIIEXT_CLDCTRL6,
				&phy_val);
			phy_val = FIELD_GETX(phy_val, CLDCTRL6_CAB_LEN);
			phy_val = phy_val > CLDCTRL6_CAB_LEN_SHORT ?
				AZ_ANADECT_LONG : AZ_ANADECT_DEF;
			atl1c_write_phy_dbg(hw, MIIDBG_AZ_ANADECT, phy_val);
		}

		if (adj_thresh && link_speed == SPEED_100 && hw->msi_lnkpatch) {
			atl1c_write_phy_dbg(hw, MIIDBG_MSE16DB, L1D_MSE16DB_UP);
			atl1c_write_phy_dbg(hw, MIIDBG_SYSMODCTRL,
				L1D_SYSMODCTRL_IECHOADJ_DEF);
		}
	} else {
		if (adj_thresh && hw->msi_lnkpatch) {
			atl1c_write_phy_dbg(hw, MIIDBG_SYSMODCTRL,
				SYSMODCTRL_IECHOADJ_DEF);
			atl1c_write_phy_dbg(hw, MIIDBG_MSE16DB,
				L1D_MSE16DB_DOWN);
		}
	}
}
