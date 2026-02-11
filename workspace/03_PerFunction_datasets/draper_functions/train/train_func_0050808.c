ipmi_user_set_password(
		       struct ipmi_intf * intf,
		       uint8_t user_id,
		       uint8_t operation,
		       const char *password,
		       int is_twenty_byte_password)
{
	struct ipmi_rs	     * rsp;
	struct ipmi_rq	       req;
	uint8_t	             * msg_data;
	uint8_t                name[17];

	if (operation == IPMI_PASSWORD_SET_PASSWORD)
	{
		memset(name, 0, 17);
		ipmi_get_user_name(intf, user_id, name);
	}

	int password_length = (is_twenty_byte_password? 20 : 16);

	msg_data = (uint8_t*)malloc(password_length + 2);


	memset(&req, 0, sizeof(req));
	req.msg.netfn    = IPMI_NETFN_APP;
	req.msg.cmd	 = IPMI_SET_USER_PASSWORD;
	req.msg.data     = msg_data;
	req.msg.data_len = password_length + 2;


	msg_data[0] = user_id;

	if (is_twenty_byte_password)
		msg_data[0] |= 0x80;

	msg_data[1] = operation;

	memset(msg_data + 2, 0, password_length);

	if (password != NULL)
		strncpy((char *)(msg_data + 2), password, password_length);

	rsp = intf->sendrecv(intf, &req);

	if (rsp == NULL) {
		lprintf(LOG_ERR, "Set User Password command failed (user %d)",
			user_id);
		return -1;
	}
	if (rsp->ccode > 0) {
		lprintf(LOG_ERR, "Set User Password command failed (user %d): %s",
			user_id, val2str(rsp->ccode, completion_code_vals));
		return rsp->ccode;
	}

	if (operation == IPMI_PASSWORD_SET_PASSWORD &&
		strncmp(name, intf->session->username, 16) == 0)
	{
		ipmi_intf_session_set_password(intf, password);
	}

	return 0;
}
