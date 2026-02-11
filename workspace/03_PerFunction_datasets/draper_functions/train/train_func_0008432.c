ipmi_sel_delete(struct ipmi_intf * intf, int argc, char ** argv)
{
	struct ipmi_rs * rsp;
	struct ipmi_rq req;
	uint16_t id;
	uint8_t msg_data[4];
	int rc = 0;

	if (argc == 0 || strncmp(argv[0], "help", 4) == 0) {
		lprintf(LOG_ERR, "usage: delete <id>...<id>\n");
		return -1;
	}

	if (ipmi_sel_reserve(intf, &id) < 0)
		return -1;

	memset(msg_data, 0, 4);
	msg_data[0] = id & 0xff;
	msg_data[1] = id >> 8;

	for (; argc != 0; argc--)
	{
		id = (uint16_t) strtoul(argv[argc-1], NULL, 0);
		msg_data[2] = id & 0xff;
		msg_data[3] = id >> 8;

		memset(&req, 0, sizeof(req));
		req.msg.netfn = IPMI_NETFN_STORAGE;
		req.msg.cmd = IPMI_CMD_DELETE_SEL_ENTRY;
		req.msg.data = msg_data;
		req.msg.data_len = 4;

		rsp = intf->sendrecv(intf, &req);
		if (rsp == NULL) {
			lprintf(LOG_ERR, "Unable to delete entry %d", id);
			rc = -1;
		}
		else if (rsp->ccode > 0) {
			lprintf(LOG_ERR, "Unable to delete entry %d: %s", id,
				val2str(rsp->ccode, completion_code_vals));
			rc = -1;
		}
		else {
			printf("Deleted entry %d\n", id);
		}
	}

	return rc;
}
