ath5k_setup_bands(struct net80211_device *dev)
{
	struct ath5k_softc *sc = dev->priv;
	struct ath5k_hw *ah = sc->ah;
	int max_c, count_c = 0;
	int i;
	int band;

	max_c = sizeof(sc->hwinfo->channels) / sizeof(sc->hwinfo->channels[0]);


	if (sc->ah->ah_capabilities.cap_mode & AR5K_MODE_BIT_11G) {

		band = NET80211_BAND_2GHZ;
		sc->hwinfo->bands = NET80211_BAND_BIT_2GHZ;
		sc->hwinfo->modes = (NET80211_MODE_G | NET80211_MODE_B);

		for (i = 0; i < 12; i++)
			sc->hwinfo->rates[band][i] = ath5k_rates[i].bitrate;
		sc->hwinfo->nr_rates[band] = 12;

		sc->hwinfo->nr_channels =
			ath5k_copy_channels(ah, sc->hwinfo->channels,
					    AR5K_MODE_11G, max_c);
		count_c = sc->hwinfo->nr_channels;
		max_c -= count_c;
	} else if (sc->ah->ah_capabilities.cap_mode & AR5K_MODE_BIT_11B) {

		band = NET80211_BAND_2GHZ;
		sc->hwinfo->bands = NET80211_BAND_BIT_2GHZ;
		sc->hwinfo->modes = NET80211_MODE_B;

		for (i = 0; i < 4; i++)
			sc->hwinfo->rates[band][i] = ath5k_rates[i].bitrate;
		sc->hwinfo->nr_rates[band] = 4;

		sc->hwinfo->nr_channels =
			ath5k_copy_channels(ah, sc->hwinfo->channels,
					    AR5K_MODE_11B, max_c);
		count_c = sc->hwinfo->nr_channels;
		max_c -= count_c;
	}


	if (sc->ah->ah_capabilities.cap_mode & AR5K_MODE_BIT_11A) {
		band = NET80211_BAND_5GHZ;
		sc->hwinfo->bands |= NET80211_BAND_BIT_5GHZ;
		sc->hwinfo->modes |= NET80211_MODE_A;

		for (i = 0; i < 8; i++)
			sc->hwinfo->rates[band][i] = ath5k_rates[i+4].bitrate;
		sc->hwinfo->nr_rates[band] = 8;

		sc->hwinfo->nr_channels =
			ath5k_copy_channels(ah, sc->hwinfo->channels,
					    AR5K_MODE_11B, max_c);
		count_c = sc->hwinfo->nr_channels;
		max_c -= count_c;
	}

	return 0;
}
