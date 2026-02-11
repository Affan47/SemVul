ipmi_lan_send_sol_payload(struct ipmi_intf * intf,
			  struct ipmi_v2_payload * payload)
{
	struct ipmi_rs      * rsp = NULL;
	uint8_t             * msg;
	int                   len;
	int                   try = 0;

	if (intf->opened == 0 && intf->open != NULL) {
		if (intf->open(intf) < 0)
			return NULL;
	}

	msg = ipmi_lan_build_sol_msg(intf, payload, &len);
	if (len <= 0 || msg == NULL) {
		lprintf(LOG_ERR, "Invalid SOL payload packet");
		if (msg != NULL)
			free(msg);
		return NULL;
	}

	lprintf(LOG_DEBUG, ">> SENDING A SOL MESSAGE\n");

	for (;;) {
		if (ipmi_lan_send_packet(intf, msg, len) < 0) {
			try++;
			usleep(5000);
			continue;
		}


		if (intf->noanswer)
			break;

		if (payload->payload.sol_packet.packet_sequence_number == 0) {

			break;
		}

		usleep(100);

		rsp = ipmi_lan_recv_sol(intf);

		if (sol_response_acks_packet(rsp, payload))
			break;

		else if (is_sol_packet(rsp) && rsp->data_len)
		{


			intf->session->sol_data.sol_input_handler(rsp);
		}

		usleep(5000);
		if (++try >= intf->session->retry) {
			lprintf(LOG_DEBUG, "  No response from remote controller");
			break;
		}
	}

	return rsp;
}
