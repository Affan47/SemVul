il4965_txq_check_empty(struct il_priv *il, int sta_id, u8 tid, int txq_id)
{
	struct il_queue *q = &il->txq[txq_id].q;
	u8 *addr = il->stations[sta_id].sta.sta.addr;
	struct il_tid_data *tid_data = &il->stations[sta_id].tid[tid];

	lockdep_assert_held(&il->sta_lock);

	switch (il->stations[sta_id].tid[tid].agg.state) {
	case IL_EMPTYING_HW_QUEUE_DELBA:


		if (txq_id == tid_data->agg.txq_id &&
		    q->read_ptr == q->write_ptr) {
			u16 ssn = IEEE80211_SEQ_TO_SN(tid_data->seq_number);
			int tx_fifo = il4965_get_fifo_from_tid(tid);
			D_HT("HW queue empty: continue DELBA flow\n");
			il4965_txq_agg_disable(il, txq_id, ssn, tx_fifo);
			tid_data->agg.state = IL_AGG_OFF;
			ieee80211_stop_tx_ba_cb_irqsafe(il->vif, addr, tid);
		}
		break;
	case IL_EMPTYING_HW_QUEUE_ADDBA:

		if (tid_data->tfds_in_queue == 0) {
			D_HT("HW queue empty: continue ADDBA flow\n");
			tid_data->agg.state = IL_AGG_ON;
			ieee80211_start_tx_ba_cb_irqsafe(il->vif, addr, tid);
		}
		break;
	}

	return 0;
}
