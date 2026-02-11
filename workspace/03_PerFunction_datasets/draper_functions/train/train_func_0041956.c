cleanup_device_data(struct hfi1_devdata *dd)
{
	int ctxt;
	int pidx;
	struct hfi1_ctxtdata **tmp;
	unsigned long flags;


	for (pidx = 0; pidx < dd->num_pports; ++pidx) {
		struct hfi1_pportdata *ppd = &dd->pport[pidx];
		struct cc_state *cc_state;
		int i;

		if (ppd->statusp)
			*ppd->statusp &= ~HFI1_STATUS_CHIP_PRESENT;

		for (i = 0; i < OPA_MAX_SLS; i++)
			hrtimer_cancel(&ppd->cca_timer[i].hrtimer);

		spin_lock(&ppd->cc_state_lock);
		cc_state = get_cc_state(ppd);
		rcu_assign_pointer(ppd->cc_state, NULL);
		spin_unlock(&ppd->cc_state_lock);

		if (cc_state)
			call_rcu(&cc_state->rcu, cc_state_reclaim);
	}

	free_credit_return(dd);


	spin_lock_irqsave(&dd->uctxt_lock, flags);
	tmp = dd->rcd;
	dd->rcd = NULL;
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);
	for (ctxt = 0; tmp && ctxt < dd->num_rcv_contexts; ctxt++) {
		struct hfi1_ctxtdata *rcd = tmp[ctxt];

		tmp[ctxt] = NULL;
		if (rcd) {
			hfi1_clear_tids(rcd);
			hfi1_free_ctxtdata(dd, rcd);
		}
	}
	kfree(tmp);

	for (ctxt = 0; ctxt < dd->num_send_contexts; ctxt++)
		sc_free(dd->send_contexts[ctxt].sc);
	dd->num_send_contexts = 0;
	kfree(dd->send_contexts);
	dd->send_contexts = NULL;
	kfree(dd->boardname);
	vfree(dd->events);
	vfree(dd->status);
	hfi1_cq_exit(dd);
}
