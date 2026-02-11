htc_process_credit_report(struct htc_target *target,
				      struct htc_credit_report *rpt,
				      int num_entries,
				      enum htc_endpoint_id from_ep)
{
	int total_credits = 0, i;
	struct htc_endpoint *ep;


	spin_lock_bh(&target->tx_lock);

	for (i = 0; i < num_entries; i++, rpt++) {
		if (rpt->eid >= ENDPOINT_MAX) {
			WARN_ON_ONCE(1);
			spin_unlock_bh(&target->tx_lock);
			return;
		}

		ep = &target->endpoint[rpt->eid];
		ep->cred_dist.credits += rpt->credits;

		if (ep->cred_dist.credits && get_queue_depth(&ep->txq)) {
			spin_unlock_bh(&target->tx_lock);
			htc_try_send(target, ep, NULL);
			spin_lock_bh(&target->tx_lock);
		}

		total_credits += rpt->credits;
	}
	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "Report indicated %d credits to distribute\n",
		   total_credits);

	spin_unlock_bh(&target->tx_lock);
}
