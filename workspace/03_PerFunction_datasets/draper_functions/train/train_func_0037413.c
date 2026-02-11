bna_tx_enet_stop(struct bna_tx *tx)
{
	struct bna_txq *txq;


	list_for_each_entry(txq, &tx->txq_q, qe)
		bna_ib_stop(tx->bna, &txq->ib);

	bna_bfi_tx_enet_stop(tx);
}
