ath_tx_txqaddbuf(struct ath_softc *sc, struct ath_txq *txq,
			     struct list_head *head)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath_buf *bf;


	if (list_empty(head))
		return;

	bf = list_first_entry(head, struct ath_buf, list);

	DBGIO("ath9k: "
		"qnum: %d, txq depth: %d\n", txq->axq_qnum, txq->axq_depth);

	list_splice_tail_init(head, &txq->axq_q);

	if (txq->axq_link == NULL) {
		ath9k_hw_puttxbuf(ah, txq->axq_qnum, bf->bf_daddr);
		DBGIO("ath9k: TXDP[%d] = %llx (%p)\n",
			txq->axq_qnum, ito64(bf->bf_daddr),
			bf->bf_desc);
	} else {
		*txq->axq_link = bf->bf_daddr;
		DBGIO("ath9k: "
			"link[%d] (%p)=%llx (%p)\n",
			txq->axq_qnum, txq->axq_link,
			ito64(bf->bf_daddr), bf->bf_desc);
	}
	ath9k_hw_get_desc_link(ah, bf->bf_lastbf->bf_desc,
			       &txq->axq_link);
	ath9k_hw_txstart(ah, txq->axq_qnum);

	txq->axq_depth++;
}
