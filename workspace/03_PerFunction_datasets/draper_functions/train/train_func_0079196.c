ath5k_txq_drainq(struct ath5k_softc *sc, struct ath5k_txq *txq)
{
	struct ath5k_buf *bf, *bf0;

	list_for_each_entry_safe(bf, bf0, &txq->q, list) {
		ath5k_txbuf_free(sc, bf);

		list_del(&bf->list);
		list_add_tail(&bf->list, &sc->txbuf);
		sc->txbuf_len++;
	}
	txq->link = NULL;
}
