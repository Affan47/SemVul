ath9k_init_misc(struct ath_softc *sc)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	int i = 0;

	setup_timer(&common->ani.timer, ath_ani_calibrate, (unsigned long)sc);

	common->last_rssi = ATH_RSSI_DUMMY_MARKER;
	memcpy(common->bssidmask, ath_bcast_mac, ETH_ALEN);
	sc->beacon.slottime = ATH9K_SLOT_TIME_9;

	for (i = 0; i < ARRAY_SIZE(sc->beacon.bslot); i++)
		sc->beacon.bslot[i] = NULL;

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_ANT_DIV_COMB)
		sc->ant_comb.count = ATH_ANT_DIV_COMB_INIT_COUNT;

	sc->spec_priv.ah = sc->sc_ah;
	sc->spec_priv.spec_config.enabled = 0;
	sc->spec_priv.spec_config.short_repeat = true;
	sc->spec_priv.spec_config.count = 8;
	sc->spec_priv.spec_config.endless = false;
	sc->spec_priv.spec_config.period = 0xFF;
	sc->spec_priv.spec_config.fft_period = 0xF;
}
