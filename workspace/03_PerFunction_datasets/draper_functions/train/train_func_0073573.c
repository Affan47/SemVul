ho_byname2(struct irs_ho *this, const char *name, int af) {
	struct pvt *pvt = (struct pvt *)this->private;
	struct hostent *ho = &pvt->host;
	char *body = NULL;
	size_t bodylen;
	int code;
	char text[256];

	if (ho->h_name != NULL &&
	    strcmp(name, ho->h_name) == 0 &&
	    af == ho->h_addrtype) {
		return (ho);
	}

	if (irs_irp_connection_setup(pvt->girpdata, &pvt->warned) != 0) {
		return (NULL);
	}

	if (irs_irp_send_command(pvt->girpdata, "gethostbyname2 %s %s",
				 name, ADDR_T_STR(af)) != 0)
		return (NULL);

	if (irs_irp_get_full_response(pvt->girpdata, &code,
				      text, sizeof text,
				      &body, &bodylen) != 0) {
		return (NULL);
	}

	if (code == IRPD_GETHOST_OK) {
		free_host(ho);
		if (irp_unmarshall_ho(ho, body) != 0) {
			ho = NULL;
		}
	} else {
		ho = NULL;
	}

	if (body != NULL) {
		memput(body, bodylen);
	}

	return (ho);
}
