cfg_initiator_recv_ATTR(struct message *msg)
{
	struct payload *attrp = payload_first(msg, ISAKMP_PAYLOAD_ATTRIBUTE);
	struct ipsec_exch *ie = msg->exchange->data;
	struct sa      *isakmp_sa = msg->isakmp_sa;
	struct isakmp_cfg_attr *attr;
	struct sockaddr *sa;
	const char     *uk_addr = "<unknown>";
	char           *addr;

	if (msg->exchange->phase == 2)
		if (cfg_verify_hash(msg))
			return -1;


	if (ie->cfg_id != GET_ISAKMP_ATTRIBUTE_ID(attrp->p)) {
		log_print("cfg_initiator_recv_ATTR: "
		    "cfg packet ID does not match!");
		message_drop(msg, ISAKMP_NOTIFY_PAYLOAD_MALFORMED, 0, 1, 0);
		return -1;
	}
	switch (attrp->p[ISAKMP_ATTRIBUTE_TYPE_OFF]) {
	case ISAKMP_CFG_ACK:
		if (ie->cfg_type != ISAKMP_CFG_SET) {
			log_print("cfg_initiator_recv_ATTR: "
			    "bad packet type ACK");
			message_drop(msg, ISAKMP_NOTIFY_PAYLOAD_MALFORMED,
			    0, 1, 0);
			return -1;
		}
		break;
	case ISAKMP_CFG_REPLY:
		if (ie->cfg_type != ISAKMP_CFG_REQUEST) {
			log_print("cfg_initiator_recv_ATTR: "
			    "bad packet type REPLY");
			message_drop(msg, ISAKMP_NOTIFY_PAYLOAD_MALFORMED,
			    0, 1, 0);
			return -1;
		}
		break;

	default:
		log_print("cfg_initiator_recv_ATTR: unexpected configuration "
		    "message type %d", attrp->p[ISAKMP_ATTRIBUTE_TYPE_OFF]);
		message_drop(msg, ISAKMP_NOTIFY_PAYLOAD_MALFORMED, 0, 1, 0);
		return -1;
	}

	attribute_map(attrp->p + ISAKMP_ATTRIBUTE_ATTRS_OFF,
	    GET_ISAKMP_GEN_LENGTH(attrp->p) - ISAKMP_TRANSFORM_SA_ATTRS_OFF,
	    cfg_decode_attribute, ie);

	switch (ie->cfg_type) {
	case ISAKMP_CFG_ACK: {

			msg->transport->vtbl->get_src(isakmp_sa->transport,
			    &sa);
			if (sockaddr2text(sa, &addr, 0) < 0)
				addr = (char *) uk_addr;

			for (attr = LIST_FIRST(&ie->attrs); attr;
			    attr = LIST_NEXT(attr, link))
				LOG_DBG((LOG_NEGOTIATION, 50,
				    "cfg_initiator_recv_ATTR: "
				    "client %s ACKs attribute %s", addr,
				    constant_name(isakmp_cfg_attr_cst,
					attr->type)));

			if (addr != uk_addr)
				free(addr);
		}
		break;

	case ISAKMP_CFG_REPLY: {


			msg->transport->vtbl->get_src(isakmp_sa->transport,
			    &sa);
			if (sockaddr2text(sa, &addr, 0) < 0)
				addr = (char *) uk_addr;

			for (attr = LIST_FIRST(&ie->attrs); attr;
			    attr = LIST_NEXT(attr, link))
				LOG_DBG((LOG_NEGOTIATION, 50,
				    "cfg_initiator_recv_ATTR: "
				    "server %s replied with attribute %s",
				    addr, constant_name(isakmp_cfg_attr_cst,
					attr->type)));

			if (addr != uk_addr)
				free(addr);
		}
		break;

	default:
		break;
	}

	attrp->flags |= PL_MARK;
	return 0;
}
