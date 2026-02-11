ath5k_beacon_update_timers(struct ath5k_hw *ah, u64 bc_tsf)
{
	u32 nexttbtt, intval, hw_tu, bc_tu;
	u64 hw_tsf;

	intval = ah->bintval & AR5K_BEACON_PERIOD;
	if (ah->opmode == NL80211_IFTYPE_AP && ah->num_ap_vifs
		+ ah->num_mesh_vifs > 1) {
		intval /= ATH_BCBUF;
		if (intval < 15)
			ATH5K_WARN(ah, "intval %u is too low, min 15\n",
				   intval);
	}
	if (WARN_ON(!intval))
		return;


	bc_tu = TSF_TO_TU(bc_tsf);


	hw_tsf = ath5k_hw_get_tsf64(ah);
	hw_tu = TSF_TO_TU(hw_tsf);

#define FUDGE (AR5K_TUNE_SW_BEACON_RESP + 3)


	if (bc_tsf == -1) {


		nexttbtt = roundup(hw_tu + FUDGE, intval);
	} else if (bc_tsf == 0) {


		nexttbtt = intval;
		intval |= AR5K_BEACON_RESET_TSF;
	} else if (bc_tsf > hw_tsf) {


		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON,
			"need to wait for HW TSF sync\n");
		return;
	} else {


		nexttbtt = bc_tu + roundup(hw_tu + FUDGE - bc_tu, intval);
	}
#undef FUDGE

	ah->nexttbtt = nexttbtt;

	intval |= AR5K_BEACON_ENA;
	ath5k_hw_init_beacon_timers(ah, nexttbtt, intval);


	if (bc_tsf == -1)
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON,
			"reconfigured timers based on HW TSF\n");
	else if (bc_tsf == 0)
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON,
			"reset HW TSF and timers\n");
	else
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON,
			"updated timers based on beacon TSF\n");

	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON,
			  "bc_tsf %llx hw_tsf %llx bc_tu %u hw_tu %u nexttbtt %u\n",
			  (unsigned long long) bc_tsf,
			  (unsigned long long) hw_tsf, bc_tu, hw_tu, nexttbtt);
	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON, "intval %u %s %s\n",
		intval & AR5K_BEACON_PERIOD,
		intval & AR5K_BEACON_ENA ? "AR5K_BEACON_ENA" : "",
		intval & AR5K_BEACON_RESET_TSF ? "AR5K_BEACON_RESET_TSF" : "");
}
