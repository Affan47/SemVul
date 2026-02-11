ipmi_lanplus_close(struct ipmi_intf * intf)
{
	if (!intf->abort)
		ipmi_close_session_cmd(intf);

	if (intf->fd >= 0)
		close(intf->fd);

	ipmi_req_clear_entries();

	if (intf->session) {
		free(intf->session);
		intf->session = NULL;
	}

	intf->session = NULL;
	intf->opened = 0;
	intf->manufacturer_id = IPMI_OEM_UNKNOWN;
	intf = NULL;
}
