mvs_sig_time_out(unsigned long tphy)
{
	struct mvs_phy *phy = (struct mvs_phy *)tphy;
	struct mvs_info *mvi = phy->mvi;
	u8 phy_no;

	for (phy_no = 0; phy_no < mvi->chip->n_phy; phy_no++) {
		if (&mvi->phy[phy_no] == phy) {
			mv_dprintk("Get signature time out, reset phy %d\n",
				phy_no+mvi->id*mvi->chip->n_phy);
			MVS_CHIP_DISP->phy_reset(mvi, phy_no, MVS_HARD_RESET);
		}
	}
}
