isns_msg_complete(struct isns_partial_msg *msg)
{
	buf_t	*msg_buf, **chain, *bp;


	if (((~msg->imp_flags) & (ISNS_F_FIRST_PDU|ISNS_F_LAST_PDU)))
		return 0;


	if (msg->imp_first_seq == msg->imp_last_seq) {
		msg->imp_payload = msg->imp_chain;
		buf_pull(msg->imp_payload, sizeof(struct isns_hdr));
		msg->imp_chain = NULL;
		return 1;
	}


	if (msg->imp_last_seq - msg->imp_first_seq + 1
			!= msg->imp_pdu_count)
		return 0;

	msg_buf = buf_alloc(msg->imp_msg_size);

	chain = &msg->imp_chain;
	while ((bp = *chain) != NULL) {

		buf_pull(bp, sizeof(struct isns_hdr));
		buf_put(msg_buf, buf_head(bp), buf_avail(bp));

		*chain = bp->next;
		buf_free(bp);
	}

	return 0;
}
