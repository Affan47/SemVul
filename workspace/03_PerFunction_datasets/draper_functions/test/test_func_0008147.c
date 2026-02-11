handle_response(struct avctp *session, struct avctp_header *avctp,
				struct avc_header *avc, uint8_t *operands,
				size_t operand_count)
{
	GSList *l;

	for (l = session->handlers; l; l = l->next) {
		struct avctp_rsp_handler *handler = l->data;

		if (handler->id != avctp->transaction)
			continue;

		if (handler->func && handler->func(session, avc->code,
						avc->subunit_type,
						operands, operand_count,
						handler->user_data))
			return;

		session->handlers = g_slist_remove(session->handlers, handler);
		g_free(handler);

		return;
	}
}
