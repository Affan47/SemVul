ath_edma_get_next_rx_buf(struct ath_softc *sc,
						struct ath_rx_status *rs,
						enum ath9k_rx_qtype qtype)
{
	struct ath_rxbuf *bf = NULL;

	while (ath_edma_get_buffers(sc, qtype, rs, &bf)) {
		if (!bf)
			continue;

		return bf;
	}
	return NULL;
}
