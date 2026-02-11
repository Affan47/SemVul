ipmi_lan_set_max_rq_data_size(struct ipmi_intf * intf, uint16_t size)
{
	if (size + 7 > 0xFF) {
		size = 0xFF - 7;
 	}

	intf->max_request_data_size = size;
}
