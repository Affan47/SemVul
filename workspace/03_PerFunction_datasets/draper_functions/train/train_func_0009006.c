check_ring_db(struct adapter *adap, struct sge_qset *qs,
			  unsigned int sleeping)
{
	if (sleeping & F_RSPD_TXQ0_GTS) {
		struct sge_txq *txq = &qs->txq[TXQ_ETH];

		if (txq->cleaned + txq->in_use != txq->processed &&
		    !test_and_set_bit(TXQ_LAST_PKT_DB, &txq->flags)) {
			set_bit(TXQ_RUNNING, &txq->flags);
			t3_write_reg(adap, A_SG_KDOORBELL, F_SELEGRCNTX |
				     V_EGRCNTX(txq->cntxt_id));
		}
	}

	if (sleeping & F_RSPD_TXQ1_GTS) {
		struct sge_txq *txq = &qs->txq[TXQ_OFLD];

		if (txq->cleaned + txq->in_use != txq->processed &&
		    !test_and_set_bit(TXQ_LAST_PKT_DB, &txq->flags)) {
			set_bit(TXQ_RUNNING, &txq->flags);
			t3_write_reg(adap, A_SG_KDOORBELL, F_SELEGRCNTX |
				     V_EGRCNTX(txq->cntxt_id));
		}
	}
}
