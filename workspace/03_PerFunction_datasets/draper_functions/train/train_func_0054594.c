ath_stoprecv(struct ath_softc *sc)
{
	struct ath_hw *ah = sc->sc_ah;
	bool stopped, reset = false;

	ath9k_hw_abortpcurecv(ah);
	ath9k_hw_setrxfilter(ah, 0);
	stopped = ath9k_hw_stopdmarecv(ah, &reset);

	ath_flushrecv(sc);

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		ath_edma_stop_recv(sc);
	else
		sc->rx.rxlink = NULL;

	if (!(ah->ah_flags & AH_UNPLUGGED) &&
	    unlikely(!stopped)) {
		ath_dbg(ath9k_hw_common(sc->sc_ah), RESET,
			"Failed to stop Rx DMA\n");
		RESET_STAT_INC(sc, RESET_RX_DMA_ERROR);
	}
	return stopped && !reset;
}
