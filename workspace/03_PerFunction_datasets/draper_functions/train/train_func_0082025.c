b43_gphy_op_recalc_txpower(struct b43_wldev *dev,
							bool ignore_tssi)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	unsigned int average_tssi;
	int cck_result, ofdm_result;
	int estimated_pwr, desired_pwr, pwr_adjust;
	int rfatt_delta, bbatt_delta;
	unsigned int max_pwr;


	cck_result = b43_phy_shm_tssi_read(dev, B43_SHM_SH_TSSI_CCK);
	ofdm_result = b43_phy_shm_tssi_read(dev, B43_SHM_SH_TSSI_OFDM_G);
	if ((cck_result < 0) && (ofdm_result < 0)) {

		if (!ignore_tssi)
			goto no_adjustment_needed;
		cck_result = 0;
		ofdm_result = 0;
	}
	if (cck_result < 0)
		average_tssi = ofdm_result;
	else if (ofdm_result < 0)
		average_tssi = cck_result;
	else
		average_tssi = (cck_result + ofdm_result) / 2;

	if (likely(gphy->average_tssi != 0xFF))
		average_tssi = (average_tssi + gphy->average_tssi) / 2;
	gphy->average_tssi = average_tssi;
	B43_WARN_ON(average_tssi >= B43_TSSI_MAX);


	estimated_pwr = b43_gphy_estimate_power_out(dev, average_tssi);

	B43_WARN_ON(phy->type != B43_PHYTYPE_G);
	max_pwr = dev->dev->bus_sprom->maxpwr_bg;
	if (dev->dev->bus_sprom->boardflags_lo & B43_BFL_PACTRL)
		max_pwr -= 3;
	if (unlikely(max_pwr >= INT_TO_Q52(30))) {
		b43warn(dev->wl,
			"Invalid max-TX-power value in SPROM.\n");
		max_pwr = INT_TO_Q52(20);
		dev->dev->bus_sprom->maxpwr_bg = max_pwr;
	}


	if (phy->desired_txpower < 0)
		desired_pwr = INT_TO_Q52(0);
	else
		desired_pwr = INT_TO_Q52(phy->desired_txpower);

	desired_pwr = clamp_val(desired_pwr, 0, max_pwr);
	if (b43_debug(dev, B43_DBG_XMITPOWER)) {
		b43dbg(dev->wl,
		       "[TX power]  current = " Q52_FMT
		       " dBm,  desired = " Q52_FMT
		       " dBm,  max = " Q52_FMT "\n",
		       Q52_ARG(estimated_pwr),
		       Q52_ARG(desired_pwr),
		       Q52_ARG(max_pwr));
	}


	pwr_adjust = desired_pwr - estimated_pwr;
	if (pwr_adjust == 0)
		goto no_adjustment_needed;


	rfatt_delta = ((pwr_adjust + 7) / 8);

	rfatt_delta = -rfatt_delta;


	bbatt_delta = pwr_adjust / 2;

	bbatt_delta = -bbatt_delta;


	bbatt_delta -= 4 * rfatt_delta;

#if B43_DEBUG
	if (b43_debug(dev, B43_DBG_XMITPOWER)) {
		int dbm = pwr_adjust < 0 ? -pwr_adjust : pwr_adjust;
		b43dbg(dev->wl,
		       "[TX power deltas]  %s" Q52_FMT " dBm   =>   "
		       "bbatt-delta = %d,  rfatt-delta = %d\n",
		       (pwr_adjust < 0 ? "-" : ""), Q52_ARG(dbm),
		       bbatt_delta, rfatt_delta);
	}
#endif


	if ((rfatt_delta == 0) && (bbatt_delta == 0))
		goto no_adjustment_needed;


	gphy->bbatt_delta = bbatt_delta;
	gphy->rfatt_delta = rfatt_delta;


	return B43_TXPWR_RES_NEED_ADJUST;

no_adjustment_needed:
	return B43_TXPWR_RES_DONE;
}
