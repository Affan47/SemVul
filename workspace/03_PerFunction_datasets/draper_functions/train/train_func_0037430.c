ipmi_serial_term_send_cmd(struct ipmi_intf * intf, struct ipmi_rq * req)
{
	static struct ipmi_rs rsp;
	uint8_t msg[IPMI_SERIAL_MAX_RESPONSE], * resp = msg;
	struct serial_term_request_ctx req_ctx[2];
	int retry, rv, msg_len, bridging_level;

	if (!intf->opened && intf->open && intf->open(intf) < 0) {
		return NULL;
	}


	for (retry = 0; retry < intf->session->retry; retry++) {

		bridging_level = serial_term_build_msg(intf, req, msg,
				sizeof (msg), req_ctx, &msg_len);
		if (msg_len < 0) {
			return NULL;
		}


		serial_flush(intf);
		serial_term_send_msg(intf, msg, msg_len);


		rv = serial_term_wait_response(intf, &req_ctx[0], msg, sizeof (msg));


		if (rv < 0) {
			return NULL;
		}


		if (rv == 0) {
			continue;
		}


		if (bridging_level && msg[0] == 0) {

			if (is_system) {

				rv = serial_term_get_message(intf, &req_ctx[1],
						msg, sizeof (msg));


				if (rv < 0) {
					return NULL;
				}


				if (rv == 0) {
					continue;
				}

			} else if (rv == 1) {

				rv = serial_term_wait_response(intf, &req_ctx[1],
						msg, sizeof (msg));


				if (rv < 0) {
					return NULL;
				}


				if (rv == 0) {
					continue;
				}
			} else {

				resp = msg + sizeof (struct ipmb_msg_hdr) + 1;

				rv -=  + sizeof (struct ipmb_msg_hdr) + 2;
			}


			if (resp[0] == 0 && bridging_level == 2 && rv < 8) {
				lprintf(LOG_ERR, "ipmitool: Message response is too short");

				return NULL;
			}
		}


		if (bridging_level == 2 && resp[0] == 0) {

			rsp.ccode = resp[7];
			rsp.data_len = rv - 9;
			memcpy(rsp.data, resp + 8, rsp.data_len);
		} else {
			rsp.ccode = resp[0];
			rsp.data_len = rv - 1;
			memcpy(rsp.data, resp + 1, rsp.data_len);
		}


		return &rsp;
	}


	return NULL;
}
