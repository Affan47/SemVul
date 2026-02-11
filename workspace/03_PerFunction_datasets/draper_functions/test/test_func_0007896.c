b43_generate_tx_phy_ctl1(struct b43_wldev *dev, u8 bitrate)
{
	const struct b43_phy *phy = &dev->phy;
	const struct b43_tx_legacy_rate_phy_ctl_entry *e;
	u16 control = 0;
	u16 bw;

	if (phy->type == B43_PHYTYPE_LP)
		bw = B43_TXH_PHY1_BW_20;
	else
		bw = B43_TXH_PHY1_BW_20;

	if (0) {
	} else if (b43_is_cck_rate(bitrate) && phy->type != B43_PHYTYPE_LP) {
		control = bw;
	} else {
		control = bw;
		e = b43_tx_legacy_rate_phy_ctl_ent(bitrate);
		if (e) {
			control |= e->coding_rate;
			control |= e->modulation;
		}
		control |= B43_TXH_PHY1_MODE_SISO;
	}

	return control;
}
