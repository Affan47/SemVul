avrcp_handle_get_capabilities(struct avrcp_player *player,
						struct avrcp_header *pdu,
						uint8_t transaction)
{
	uint16_t len = ntohs(pdu->params_len);
	unsigned int i;

	if (len != 1)
		goto err;

	DBG("id=%u", pdu->params[0]);

	switch (pdu->params[0]) {
	case CAP_COMPANY_ID:
		for (i = 0; i < G_N_ELEMENTS(company_ids); i++) {
			set_company_id(&pdu->params[2 + i * 3],
							company_ids[i]);
		}

		pdu->params_len = htons(2 + (3 * G_N_ELEMENTS(company_ids)));
		pdu->params[1] = G_N_ELEMENTS(company_ids);

		return AVC_CTYPE_STABLE;
	case CAP_EVENTS_SUPPORTED:
		pdu->params[1] = 4;
		pdu->params[2] = AVRCP_EVENT_STATUS_CHANGED;
		pdu->params[3] = AVRCP_EVENT_TRACK_CHANGED;
		pdu->params[4] = AVRCP_EVENT_TRACK_REACHED_START;
		pdu->params[5] = AVRCP_EVENT_TRACK_REACHED_END;

		pdu->params_len = htons(2 + pdu->params[1]);
		return AVC_CTYPE_STABLE;
	}

err:
	pdu->params_len = htons(1);
	pdu->params[0] = E_INVALID_PARAM;

	return AVC_CTYPE_REJECTED;
}
