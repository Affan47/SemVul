reset_endpoint_states(struct htc_target *target)
{
	struct htc_endpoint *ep;
	int i;

	for (i = ENDPOINT_0; i < ENDPOINT_MAX; i++) {
		ep = &target->endpoint[i];
		ep->svc_id = 0;
		ep->len_max = 0;
		ep->max_txq_depth = 0;
		ep->eid = i;
		INIT_LIST_HEAD(&ep->txq);
		INIT_LIST_HEAD(&ep->pipe.tx_lookup_queue);
		INIT_LIST_HEAD(&ep->rx_bufq);
		ep->target = target;
		ep->pipe.tx_credit_flow_enabled = true;
	}
}
