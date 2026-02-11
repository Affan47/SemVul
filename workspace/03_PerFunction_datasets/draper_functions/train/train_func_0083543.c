exchange_handle_leftover_payloads(struct message *msg)
{
	struct exchange *exchange = msg->exchange;
	struct doi	*doi = exchange->doi;
	struct payload	*p;
	int	i;

	for (i = ISAKMP_PAYLOAD_SA; i < payload_index_max; i++) {
		if (i == ISAKMP_PAYLOAD_PROPOSAL ||
		    i == ISAKMP_PAYLOAD_TRANSFORM)
			continue;
		for (p = payload_first(msg, i); p;
		     p = TAILQ_NEXT(p, link)) {
			if (p->flags & PL_MARK)
				continue;
			if (!doi->handle_leftover_payload ||
			    doi->handle_leftover_payload(msg, i, p))
				LOG_DBG((LOG_EXCHANGE, 10,
				    "exchange_run: unexpected payload %s",
				    constant_name(isakmp_payload_cst, i)));
		}
	}
}
