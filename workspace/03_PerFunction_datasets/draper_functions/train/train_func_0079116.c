aggr_recv_addba_req_evt(struct ath6kl_vif *vif, u8 tid_mux, u16 seq_no,
			     u8 win_sz)
{
	struct ath6kl_sta *sta;
	struct aggr_info_conn *aggr_conn = NULL;
	struct rxtid *rxtid;
	struct rxtid_stats *stats;
	u16 hold_q_size;
	u8 tid, aid;

	if (vif->nw_type == AP_NETWORK) {
		aid = ath6kl_get_aid(tid_mux);
		sta = ath6kl_find_sta_by_aid(vif->ar, aid);
		if (sta)
			aggr_conn = sta->aggr_conn;
	} else {
		aggr_conn = vif->aggr_cntxt->aggr_conn;
	}

	if (!aggr_conn)
		return;

	tid = ath6kl_get_tid(tid_mux);
	if (tid >= NUM_OF_TIDS)
		return;

	rxtid = &aggr_conn->rx_tid[tid];
	stats = &aggr_conn->stat[tid];

	if (win_sz < AGGR_WIN_SZ_MIN || win_sz > AGGR_WIN_SZ_MAX)
		ath6kl_dbg(ATH6KL_DBG_WLAN_RX, "%s: win_sz %d, tid %d\n",
			   __func__, win_sz, tid);

	if (rxtid->aggr)
		aggr_delete_tid_state(aggr_conn, tid);

	rxtid->seq_next = seq_no;
	hold_q_size = TID_WINDOW_SZ(win_sz) * sizeof(struct skb_hold_q);
	rxtid->hold_q = kzalloc(hold_q_size, GFP_KERNEL);
	if (!rxtid->hold_q)
		return;

	rxtid->win_sz = win_sz;
	rxtid->hold_q_sz = TID_WINDOW_SZ(win_sz);
	if (!skb_queue_empty(&rxtid->q))
		return;

	rxtid->aggr = true;
}
