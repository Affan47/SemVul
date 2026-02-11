ipmi_picmg_get_led_capabilities(struct ipmi_intf * intf, int argc, char ** argv)
{
	int i;
	struct ipmi_rs * rsp;
	struct ipmi_rq req;

	unsigned char msg_data[6];

	memset(&req, 0, sizeof(req));

	req.msg.netfn = IPMI_NETFN_PICMG;
	req.msg.cmd	  = PICMG_GET_LED_COLOR_CAPABILITIES_CMD;
	req.msg.data  = msg_data;
	req.msg.data_len = 3;

	msg_data[0] = 0x00;
	if (is_fru_id(argv[0], &msg_data[1]) != 0
			|| is_led_id(argv[1], &msg_data[2]) != 0) {
		return (-1);
	}

	rsp = intf->sendrecv(intf, &req);

	if (!rsp) {
		lprintf(LOG_ERR, "No valid response received.");
		return -1;
	}

	if (rsp->ccode) {
		lprintf(LOG_ERR, "LED get capabilities failed with CC code 0x%02x",
				rsp->ccode);
		return -1;
	}

	printf("LED Color Capabilities: ");
	for ( i=0 ; i<8 ; i++ ) {
		if ( rsp->data[1] & (0x01 << i) ) {
			printf("%s, ", led_color_str[ i ]);
		}
	}
	printf("\n");

	printf("Default LED Color in\n");
	printf("      LOCAL control:  %s\n", led_color_str[ rsp->data[2] ] );
	printf("      OVERRIDE state: %s\n", led_color_str[ rsp->data[3] ] );

	return 0;
}
