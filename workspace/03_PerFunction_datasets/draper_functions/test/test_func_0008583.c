b43_gphy_op_prepare_structs(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	const void *tssi2dbm;
	int tgt_idle_tssi;
	struct b43_txpower_lo_control *lo;
	unsigned int i;


	tssi2dbm = gphy->tssi2dbm;
	tgt_idle_tssi = gphy->tgt_idle_tssi;

	lo = gphy->lo_control;


	memset(gphy, 0, sizeof(*gphy));


	gphy->tssi2dbm = tssi2dbm;
	gphy->tgt_idle_tssi = tgt_idle_tssi;
	gphy->lo_control = lo;

	memset(gphy->minlowsig, 0xFF, sizeof(gphy->minlowsig));


	for (i = 0; i < ARRAY_SIZE(gphy->nrssi); i++)
		gphy->nrssi[i] = -1000;
	for (i = 0; i < ARRAY_SIZE(gphy->nrssi_lt); i++)
		gphy->nrssi_lt[i] = i;

	gphy->lofcal = 0xFFFF;
	gphy->initval = 0xFFFF;

	gphy->interfmode = B43_INTERFMODE_NONE;


	gphy->ofdmtab_addr_direction = B43_OFDMTAB_DIRECTION_UNKNOWN;

	gphy->average_tssi = 0xFF;


	lo->tx_bias = 0xFF;
	INIT_LIST_HEAD(&lo->calib_list);
}
