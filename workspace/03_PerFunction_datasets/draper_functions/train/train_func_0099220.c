cx_data_cdb(struct ipmi_intf *intf, int access, int length,
	    unsigned int cid, unsigned int fmt, unsigned char *value)
{
	int rc = CXOEM_SUCCESS;
	struct ipmi_rs *rsp;
	struct ipmi_rq req;
	uint8_t msg_data[8 + MAX_RETURNABLE_CDB_LEN];
	char out[5];
	memset(&req, 0, sizeof(req));
	memset(msg_data, 0, sizeof(msg_data));
	req.msg.netfn = IPMI_NETFN_OEM_SS;
	req.msg.cmd = IPMI_CMD_OEM_DATA_ACCESS;
	msg_data[0] = 2;
	msg_data[1] = access;
	msg_data[2] = length & 0xff;
	msg_data[3] = (length >> 8) & 0xff;
	msg_data[4] = cid & 0xff;
	msg_data[5] = (cid >> 8) & 0xff;
	msg_data[6] = (cid >> 16) & 0xff;
	msg_data[7] = (cid >> 24) & 0xff;
	if (access == CX_DATA_ACCESS_WRITE) {
		memcpy((void *)(msg_data + 8), (void *)value, length);
		req.msg.data_len = length + 8;
	} else {
		req.msg.data_len = 8;
	}
	req.msg.data = msg_data;

	rsp = intf->sendrecv(intf, &req);
	if (rsp == NULL) {
		lprintf(LOG_ERR, "Error during cdb data command\n");
		return -1;
	}

	if (rsp->ccode > 0) {
		lprintf(LOG_ERR, "cxoem data cdb command failed: %s",
			val2str(rsp->ccode, completion_code_vals));
		return -1;
	}

	if ((rsp->ccode == 0) && (access == CX_DATA_ACCESS_READ)) {
		unsigned int value;
		unsigned int dlength = 0;
		unsigned int actual_length = 0;
		int n = 2;
		int datatype = 1;
		const char *prntfmt = " %d";

		actual_length = rsp->data[0] & 0xff;
		actual_length |= (rsp->data[1] << 8) & 0xff;
		dlength = rsp->data[2] & 0xff;
		dlength |= (rsp->data[3] << 8) & 0xff;
		if (dlength > MAX_RETURNABLE_CDB_LEN) {
			printf("CDB read length too lengthy\n");
			return -1;
		}
		printf("Data size: %d\n", dlength);
		printf("CID size :  %d\n", actual_length);
		print_value(dlength, fmt, &rsp->data[4]);
	}
	return rc;
}
