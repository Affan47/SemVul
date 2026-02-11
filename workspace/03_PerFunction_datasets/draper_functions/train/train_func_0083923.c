ath_tx_return_buffer(struct ath_softc *sc, struct ath_buf *bf)
{
	list_add_tail(&bf->list, &sc->tx.txbuf);
}
