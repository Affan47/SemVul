ipmi_picmg_get_led_properties(struct ipmi_intf * intf, int argc, char ** argv)
{
	struct ipmi_rs * rsp;
	struct ipmi_rq req;

	unsigned char msg_data[6];

	memset(&req, 0, sizeof(req));

	req.msg.netfn = IPMI_NETFN_PICMG;
	req.msg.cmd	  = PICMG_GET_FRU_LED_PROPERTIES_CMD;
	req.msg.data  = msg_data;
	req.msg.data_len = 2;

	msg_data[0] = 0x00;
	msg_data[1] = atoi(argv[0]);

	rsp = intf->sendrecv(intf, &req);

	if (!rsp) {
		printf("no response\n");
		return -1;
	}

	if (rsp->ccode) {
		printf("returned CC code 0x%02x\n", rsp->ccode);
		return -1;
	}

	printf("General Status LED Properties:  0x%2x\n\r", rsp->data[1] );
	printf("App. Specific  LED Count:       0x%2x\n\r", rsp->data[2] );

	return 0;
}
