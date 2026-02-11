l2tp_recv_OCRP(struct l2tp_sess_t *sess,
			  const struct l2tp_packet_t *pack)
{
	const struct l2tp_attr_t *assigned_sid = NULL;
	const struct l2tp_attr_t *unknown_attr = NULL;
	const struct l2tp_attr_t *attr = NULL;

	if (sess->state1 != STATE_WAIT_OCRP) {
		log_session(log_warn, sess, "discarding unexpected OCRP\n");
		return 0;
	}

	log_session(log_info2, sess, "handling OCRP\n");

	list_for_each_entry(attr, &pack->attrs, entry) {
		switch(attr->attr->id) {
		case Message_Type:
		case Random_Vector:
			break;
		case Assigned_Session_ID:
			assigned_sid = attr;
			break;
		default:
			if (attr->M)
				unknown_attr = attr;
			else
				log_session(log_warn, sess,
					    "discarding unknown attribute type"
					    " %i in OCRP\n", attr->attr->id);
			break;
		}
	}

	if (assigned_sid == NULL) {
		log_session(log_error, sess, "impossible to handle OCRP:"
			    " no Assigned Session ID present in message,"
			    " disconnecting session\n");
		l2tp_session_disconnect(sess, 2, 6);

		return -1;
	}


	log_session(log_info2, sess, "peer-sid set to %hu by OCRP\n",
		    assigned_sid->val.uint16);
	sess->peer_sid = assigned_sid->val.uint16;

	if (unknown_attr) {
		log_session(log_error, sess, "impossible to handle OCRP:"
			    " unknown mandatory attribute type %i,"
			    " disconnecting session\n",
			    unknown_attr->attr->id);
		l2tp_session_disconnect(sess, 2, 8);

		return -1;
	}

	sess->state1 = STATE_WAIT_OCCN;

	return 0;
}
