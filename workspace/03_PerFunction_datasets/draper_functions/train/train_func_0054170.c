ath_startrecv(struct ath_softc *sc)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath_rxbuf *bf, *tbf;

	if (ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) {
		ath_edma_start_recv(sc);
		return;
	}

	if (list_empty(&sc->rx.rxbuf))
		goto start_recv;

	sc->rx.buf_hold = NULL;
	sc->rx.rxlink = NULL;
	list_for_each_entry_safe(bf, tbf, &sc->rx.rxbuf, list) {
		ath_rx_buf_link(sc, bf, false);
	}


	if (list_empty(&sc->rx.rxbuf))
		goto start_recv;

	bf = list_first_entry(&sc->rx.rxbuf, struct ath_rxbuf, list);
	ath9k_hw_putrxbuf(ah, bf->bf_daddr);
	ath9k_hw_rxena(ah);

start_recv:
	ath_opmode_init(sc);
	ath9k_hw_startpcureceive(ah, sc->cur_chan->offchannel);
}
