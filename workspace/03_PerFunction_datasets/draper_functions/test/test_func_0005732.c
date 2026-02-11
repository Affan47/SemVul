ike_phase_1_initiator_recv_SA(struct message *msg)
{
	struct exchange *exchange = msg->exchange;
	struct sa      *sa = TAILQ_FIRST(&exchange->sa_list);
	struct ipsec_exch *ie = exchange->data;
	struct ipsec_sa *isa = sa->data;
	struct payload *sa_p = payload_first(msg, ISAKMP_PAYLOAD_SA);
	struct payload *prop = payload_first(msg, ISAKMP_PAYLOAD_PROPOSAL);
	struct payload *xf = payload_first(msg, ISAKMP_PAYLOAD_TRANSFORM);


	if (TAILQ_NEXT(sa_p, link) || TAILQ_NEXT(prop, link) ||
	    TAILQ_NEXT(xf, link)) {
		log_print("ike_phase_1_initiator_recv_SA: "
		    "multiple SA, proposal or transform payloads in phase 1");

		message_drop(msg, ISAKMP_NOTIFY_PAYLOAD_MALFORMED, 0, 1, 0);
		return -1;
	}

	if (message_negotiate_sa(msg, ike_phase_1_validate_prop) ||
	    !TAILQ_FIRST(&sa->protos))
		return -1;

	ipsec_decode_transform(msg, sa, TAILQ_FIRST(&sa->protos), xf->p);


	if (exchange->type != ISAKMP_EXCH_AGGRESSIVE)
		ie->group = group_get(isa->group_desc);


	sa_p->flags |= PL_MARK;

	return 0;
}
