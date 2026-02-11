ipmi_intf_session_set_password(struct ipmi_intf * intf, char * password)
{
	if (intf->session == NULL)
		return;

	memset(intf->session->authcode, 0, IPMI_AUTHCODE_BUFFER_SIZE);

	if (password == NULL) {
		intf->session->password = 0;
		return;
	}

	intf->session->password = 1;
	memcpy(intf->session->authcode, password,
	       __min(strlen(password), IPMI_AUTHCODE_BUFFER_SIZE));
}
