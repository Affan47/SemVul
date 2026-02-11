ath9k_beacon_choose_slot(struct ath_softc *sc)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_beacon_config *cur_conf = &sc->cur_chan->beacon;
	u16 intval;
	u32 tsftu;
	u64 tsf;
	int slot;

	if (sc->sc_ah->opmode != NL80211_IFTYPE_AP &&
	    sc->sc_ah->opmode != NL80211_IFTYPE_MESH_POINT) {
		ath_dbg(common, BEACON, "slot 0, tsf: %llu\n",
			ath9k_hw_gettsf64(sc->sc_ah));
		return 0;
	}

	intval = cur_conf->beacon_interval ? : ATH_DEFAULT_BINTVAL;
	tsf = ath9k_hw_gettsf64(sc->sc_ah);
	tsf += TU_TO_USEC(sc->sc_ah->config.sw_beacon_response_time);
	tsftu = TSF_TO_TU((tsf * ATH_BCBUF) >>32, tsf * ATH_BCBUF);
	slot = (tsftu % (intval * ATH_BCBUF)) / intval;

	ath_dbg(common, BEACON, "slot: %d tsf: %llu tsftu: %u\n",
		slot, tsf, tsftu / ATH_BCBUF);

	return slot;
}
