ath_set_channel(struct ath_softc *sc)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ieee80211_hw *hw = sc->hw;
	struct ath9k_channel *hchan;
	struct cfg80211_chan_def *chandef = &sc->cur_chan->chandef;
	struct ieee80211_channel *chan = chandef->chan;
	int pos = chan->hw_value;
	int old_pos = -1;
	int r;

	if (test_bit(ATH_OP_INVALID, &common->op_flags))
		return -EIO;

	if (ah->curchan)
		old_pos = ah->curchan - &ah->channels[0];

	ath_dbg(common, CONFIG, "Set channel: %d MHz width: %d\n",
		chan->center_freq, chandef->width);


	spin_lock_bh(&common->cc_lock);
	ath_update_survey_stats(sc);
	spin_unlock_bh(&common->cc_lock);

	ath9k_cmn_get_channel(hw, ah, chandef);


	if (!sc->cur_chan->offchannel && sc->cur_survey != &sc->survey[pos]) {
		if (sc->cur_survey)
			sc->cur_survey->filled &= ~SURVEY_INFO_IN_USE;

		sc->cur_survey = &sc->survey[pos];

		memset(sc->cur_survey, 0, sizeof(struct survey_info));
		sc->cur_survey->filled |= SURVEY_INFO_IN_USE;
	} else if (!(sc->survey[pos].filled & SURVEY_INFO_IN_USE)) {
		memset(&sc->survey[pos], 0, sizeof(struct survey_info));
	}

	hchan = &sc->sc_ah->channels[pos];
	r = ath_reset(sc, hchan);
	if (r)
		return r;


	if (old_pos >= 0)
		ath_update_survey_nf(sc, old_pos);


	if (hw->conf.radar_enabled) {
		u32 rxfilter;

		rxfilter = ath9k_hw_getrxfilter(ah);
		rxfilter |= ATH9K_RX_FILTER_PHYRADAR |
				ATH9K_RX_FILTER_PHYERR;
		ath9k_hw_setrxfilter(ah, rxfilter);
		ath_dbg(common, DFS, "DFS enabled at freq %d\n",
			chan->center_freq);
	} else {

		if (test_bit(ATH_OP_SCANNING, &common->op_flags) &&
			sc->spec_priv.spectral_mode == SPECTRAL_CHANSCAN)
			ath9k_cmn_spectral_scan_trigger(common, &sc->spec_priv);
	}

	return 0;
}
