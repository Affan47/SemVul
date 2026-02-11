aggr_timeout(unsigned long arg)
{
	u8 i, j;
	struct aggr_info_conn *aggr_conn = (struct aggr_info_conn *) arg;
	struct rxtid *rxtid;
	struct rxtid_stats *stats;

	for (i = 0; i < NUM_OF_TIDS; i++) {
		rxtid = &aggr_conn->rx_tid[i];
		stats = &aggr_conn->stat[i];

		if (!rxtid->aggr || !rxtid->timer_mon)
			continue;

		stats->num_timeouts++;
		ath6kl_dbg(ATH6KL_DBG_AGGR,
			   "aggr timeout (st %d end %d)\n",
			   rxtid->seq_next,
			   ((rxtid->seq_next + rxtid->hold_q_sz-1) &
			    ATH6KL_MAX_SEQ_NO));
		aggr_deque_frms(aggr_conn, i, 0, 0);
	}

	aggr_conn->timer_scheduled = false;

	for (i = 0; i < NUM_OF_TIDS; i++) {
		rxtid = &aggr_conn->rx_tid[i];

		if (rxtid->aggr && rxtid->hold_q) {
			spin_lock_bh(&rxtid->lock);
			for (j = 0; j < rxtid->hold_q_sz; j++) {
				if (rxtid->hold_q[j].skb) {
					aggr_conn->timer_scheduled = true;
					rxtid->timer_mon = true;
					break;
				}
			}
			spin_unlock_bh(&rxtid->lock);

			if (j >= rxtid->hold_q_sz)
				rxtid->timer_mon = false;
		}
	}

	if (aggr_conn->timer_scheduled)
		mod_timer(&aggr_conn->timer,
			  jiffies + msecs_to_jiffies(AGGR_RX_TIMEOUT));
}
