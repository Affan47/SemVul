ipmi_getdrivemap(struct ipmi_intf * intf, int b, int d, int f, int *bay,
		int *slot)
{
	struct ipmi_rs * rsp = NULL;
	struct ipmi_rq req = {0};
	uint8_t data[8];

	req.msg.netfn = DELL_OEM_NETFN;
	req.msg.lun = 0;
	req.msg.cmd = 0xD5;
	req.msg.data_len = 8;
	req.msg.data = data;

	memset(data, 0, sizeof(data));
	data[0] = 0x01;
	data[1] = 0x07;
	data[2] = 0x06;
	data[3] = 0x00;
	data[4] = 0x00;
	data[5] = 0x00;
	data[6] = b;
	data[7] = (d << 3) + f;

	rsp = intf->sendrecv(intf, &req);
	if (rsp == NULL) {
		lprintf(LOG_ERR, "Error issuing getdrivemap command.");
		return -1;
	} else if (rsp->ccode != 0) {
		lprintf(LOG_ERR, "Error issuing getdrivemap command: %s",
				val2str(rsp->ccode, completion_code_vals));
		return -1;
	}
	*bay = rsp->data[7];
	*slot = rsp->data[8];
	if (*bay == 0xFF || *slot == 0xFF) {
		lprintf(LOG_ERR, "Error could not get drive bay:slot mapping");
		return -1;
	}
	return 0;
}
