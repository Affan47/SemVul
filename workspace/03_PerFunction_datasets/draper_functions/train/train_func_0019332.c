update_sentinels(struct smq_policy *mq)
{
	if (time_after(jiffies, mq->next_writeback_period)) {
		__update_writeback_sentinels(mq);
		mq->next_writeback_period = jiffies + WRITEBACK_PERIOD;
		mq->current_writeback_sentinels = !mq->current_writeback_sentinels;
	}

	if (time_after(jiffies, mq->next_demote_period)) {
		__update_demote_sentinels(mq);
		mq->next_demote_period = jiffies + DEMOTE_PERIOD;
		mq->current_demote_sentinels = !mq->current_demote_sentinels;
	}
}
