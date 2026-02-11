ipmi_sdr_get_record(struct ipmi_intf * intf, struct sdr_get_rs * header,
		    struct ipmi_sdr_iterator * itr)
{
	struct ipmi_rq req;
	struct ipmi_rs *rsp;
	struct sdr_get_rq sdr_rq;
	uint8_t *data;
	int i = 0, len = header->length;

	if (len < 1)
		return NULL;

	data = malloc(len + 1);
	if (data == NULL) {
		lprintf(LOG_ERR, "ipmitool: malloc failure");
		return NULL;
	}
	memset(data, 0, len + 1);

	memset(&sdr_rq, 0, sizeof (sdr_rq));
	sdr_rq.reserve_id = itr->reservation;
	sdr_rq.id = header->id;
	sdr_rq.offset = 0;

	memset(&req, 0, sizeof (req));
	if (itr->use_built_in == 0) {
		req.msg.netfn = IPMI_NETFN_STORAGE;
		req.msg.cmd = GET_SDR;
	} else {
		req.msg.netfn = IPMI_NETFN_SE;
		req.msg.cmd = GET_DEVICE_SDR;
	}
	req.msg.data = (uint8_t *) & sdr_rq;
	req.msg.data_len = sizeof (sdr_rq);


	while (i < len) {
		sdr_rq.length = (len - i < sdr_max_read_len) ?
		    len - i : sdr_max_read_len;
		sdr_rq.offset = i + 5;

		lprintf(LOG_DEBUG, "Getting %d bytes from SDR at offset %d",
			sdr_rq.length, sdr_rq.offset);

		rsp = intf->sendrecv(intf, &req);
		if (rsp == NULL) {
		    sdr_max_read_len = sdr_rq.length - 1;
		    if (sdr_max_read_len > 0) {


			continue;
		    } else {
			free(data);
			data = NULL;
			return NULL;
		    }
		}

		switch (rsp->ccode) {
		case 0xca:

			sdr_max_read_len = sdr_rq.length - 1;
			continue;
		case 0xc5:

			lprintf(LOG_DEBUG, "SDR reservation cancelled. "
				"Sleeping a bit and retrying...");

			sleep(rand() & 3);

			if (ipmi_sdr_get_reservation(intf, itr->use_built_in,
                                      &(itr->reservation)) < 0) {
				free(data);
				data = NULL;
				return NULL;
			}
			sdr_rq.reserve_id = itr->reservation;
			continue;
		}


		if (rsp->ccode > 0 || rsp->data_len == 0) {
			free(data);
			data = NULL;
			return NULL;
		}

		memcpy(data + i, rsp->data + 2, sdr_rq.length);
		i += sdr_max_read_len;
	}

	return data;
}
