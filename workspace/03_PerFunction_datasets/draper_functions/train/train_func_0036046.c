ipmi_poll(ipmi_smi_t intf)
{
	if (intf->handlers->poll)
		intf->handlers->poll(intf->send_info);

	handle_new_recv_msgs(intf);
}
