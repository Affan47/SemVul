ath9k_process_rate(struct ath_common *common __unused,
			      struct net80211_device *dev,
			      struct ath_rx_status *rx_stats,
			      int *rix)
{
	struct ath_softc *sc = (struct ath_softc *)dev->priv;
	int band;
	int i = 0;

	band = (dev->channels + sc->dev->channel)->band;

	for (i = 0; i < sc->hwinfo->nr_rates[band]; i++) {
		if (sc->rates[i].hw_value == rx_stats->rs_rate) {
			*rix = i;
			return 0;
		}
		if (sc->rates[i].hw_value_short == rx_stats->rs_rate) {
			*rix = i;
			return 0;
		}
	}


	DBG("ath9k: "
		"unsupported hw bitrate detected 0x%02x using 1 Mbit\n",
		rx_stats->rs_rate);

	return -EINVAL;
}
