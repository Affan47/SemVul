ath5k_mode_setup(struct ath5k_softc *sc)
{
	struct ath5k_hw *ah = sc->ah;
	u32 rfilt;


	rfilt = sc->filter_flags;
	ath5k_hw_set_rx_filter(ah, rfilt);

	if (ath5k_hw_hasbssidmask(ah))
		ath5k_hw_set_bssid_mask(ah, sc->bssidmask);


	ath5k_hw_set_opmode(ah);

	ath5k_hw_set_mcast_filter(ah, 0, 0);
}
