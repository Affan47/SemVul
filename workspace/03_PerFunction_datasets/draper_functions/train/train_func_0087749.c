carl9170_debugfs_ampdu_state_read(struct ar9170 *ar, char *buf,
					       size_t bufsize, ssize_t *len)
{
	struct carl9170_sta_tid *iter;
	struct sk_buff *skb;
	int cnt = 0, fc;
	int offset;

	rcu_read_lock();
	list_for_each_entry_rcu(iter, &ar->tx_ampdu_list, list) {

		spin_lock_bh(&iter->lock);
		ADD(buf, *len, bufsize, "Entry: #%2d TID:%1d, BSN:%4d, "
		    "SNX:%4d, HSN:%4d, BAW:%2d, state:%1d, toggles:%d\n",
		    cnt, iter->tid, iter->bsn, iter->snx, iter->hsn,
		    iter->max, iter->state, iter->counter);

		ADD(buf, *len, bufsize, "\tWindow:  [%*pb,W]\n",
		    CARL9170_BAW_BITS, iter->bitmap);

#define BM_STR_OFF(offset)					\
	((CARL9170_BAW_BITS - (offset) - 1) / 4 +		\
	 (CARL9170_BAW_BITS - (offset) - 1) / 32 + 1)

		offset = BM_STR_OFF(0);
		ADD(buf, *len, bufsize, "\tBase Seq: %*s\n", offset, "T");

		offset = BM_STR_OFF(SEQ_DIFF(iter->snx, iter->bsn));
		ADD(buf, *len, bufsize, "\tNext Seq: %*s\n", offset, "W");

		offset = BM_STR_OFF(((int)iter->hsn - (int)iter->bsn) %
				     CARL9170_BAW_BITS);
		ADD(buf, *len, bufsize, "\tLast Seq: %*s\n", offset, "N");

		ADD(buf, *len, bufsize, "\tPre-Aggregation reorder buffer: "
		    " currently queued:%d\n", skb_queue_len(&iter->queue));

		fc = 0;
		skb_queue_walk(&iter->queue, skb) {
			char prefix[32];

			snprintf(prefix, sizeof(prefix), "\t\t%3d :", fc);
			carl9170_debugfs_format_frame(ar, skb, prefix, buf,
						      len, bufsize);

			fc++;
		}
		spin_unlock_bh(&iter->lock);
		cnt++;
	}
	rcu_read_unlock();

	return buf;
}
