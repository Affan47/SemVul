ib_nl_request_timeout(struct work_struct *work)
{
	unsigned long flags;
	struct ib_sa_query *query;
	unsigned long delay;
	struct ib_mad_send_wc mad_send_wc;
	int ret;

	spin_lock_irqsave(&ib_nl_request_lock, flags);
	while (!list_empty(&ib_nl_request_list)) {
		query = list_entry(ib_nl_request_list.next,
				   struct ib_sa_query, list);

		if (time_after(query->timeout, jiffies)) {
			delay = query->timeout - jiffies;
			if ((long)delay <= 0)
				delay = 1;
			queue_delayed_work(ib_nl_wq, &ib_nl_timed_work, delay);
			break;
		}

		list_del(&query->list);
		ib_sa_disable_local_svc(query);

		if (ib_sa_query_cancelled(query))
			ret = -1;
		else
			ret = ib_post_send_mad(query->mad_buf, NULL);
		if (ret) {
			mad_send_wc.send_buf = query->mad_buf;
			mad_send_wc.status = IB_WC_WR_FLUSH_ERR;
			spin_unlock_irqrestore(&ib_nl_request_lock, flags);
			send_handler(query->port->agent, &mad_send_wc);
			spin_lock_irqsave(&ib_nl_request_lock, flags);
		}
	}
	spin_unlock_irqrestore(&ib_nl_request_lock, flags);
}
