ath_bar_retry(struct ath_softc_tgt *sc, struct ath_tx_buf *bf)
{
	struct ath_node_target *an = ATH_NODE_TARGET(bf->bf_node);
	ath_atx_tid_t *tid = ATH_AN_2_TID(an, bf->bf_tidno);

	if (bf->bf_retries >= OWLMAX_BAR_RETRIES) {
		ath_tgt_delba_send(sc, bf->bf_node, tid->tidno, 1,
				   IEEE80211_REASON_UNSPECIFIED);
		ath_tgt_tid_drain(sc, tid);

		bf->bf_comp = NULL;
		ath_buf_comp(sc, bf);
		return;
	}

	__stats(sc, txbar_compretries);

	if (!bf->bf_lastds->ds_link) {
		__stats(sc, txbar_errlast);
		bf = ath_buf_toggle(sc, bf, 1);
	}

	bf->bf_lastds->ds_link = 0;

	ath_tx_set_retry(sc, bf);
	ath_tgt_txq_add_ucast(sc, bf);
}
