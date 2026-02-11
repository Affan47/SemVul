ipmi_serial_term_setup(struct ipmi_intf * intf)
{
	intf->session = malloc(sizeof(struct ipmi_session));
	if (intf->session == NULL) {
		lprintf(LOG_ERR, "ipmitool: malloc failure");
		return -1;
	}

	memset(intf->session, 0, sizeof(struct ipmi_session));


	intf->max_request_data_size = IPMI_SERIAL_MAX_RQ_SIZE;
	intf->max_response_data_size = IPMI_SERIAL_MAX_RS_SIZE;
	return 0;
}
