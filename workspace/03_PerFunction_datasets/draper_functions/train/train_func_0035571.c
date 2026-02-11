cx_fw_check(struct ipmi_intf *intf, int partition)
{
	int rc = CXOEM_SUCCESS;
	struct ipmi_rs *rsp;
	struct ipmi_rq req;
	uint8_t msg_data[64];

	memset(&req, 0, sizeof(req));
	memset(msg_data, 0, 64);
	req.msg.netfn = IPMI_NETFN_OEM_SS;
	req.msg.cmd = IPMI_CMD_OEM_FW_GET_STATUS;
	msg_data[0] = 0;
	msg_data[1] = 4;
	msg_data[2] = partition;
	req.msg.data = msg_data;
	req.msg.data_len = 3;

	rsp = intf->sendrecv(intf, &req);
	if (rsp == NULL) {
		lprintf(LOG_ERR, "Error during firmware check");
		return -1;
	}

	if (rsp->ccode == 0) {
		if (rsp->data[1] == 0) {
			unsigned int crc32;
			crc32 = (unsigned int)rsp->data[5];
			crc32 |= (unsigned int)(rsp->data[4] << 8);
			crc32 |= (unsigned int)(rsp->data[3] << 16);
			crc32 |= (unsigned int)(rsp->data[2] << 24);
			printf("CRC32             : %08x\n", crc32);
		} else {
			lprintf(LOG_ERR, "Error: %s",
				val2str(rsp->data[1], cx_fw_check_errors));
			return -1;
		}
	} else if (rsp->ccode > 0) {
		lprintf(LOG_ERR, "Error: %s",
			val2str(rsp->ccode, completion_code_vals));
		return -1;
	}

	return rc;
}
