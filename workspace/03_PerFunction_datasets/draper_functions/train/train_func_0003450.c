_get_subfn_enables(struct ipmi_intf * intf,
	struct ipmi_function_params * p, struct command_support * cmd)
{
	struct ipmi_rs * rsp;
	struct ipmi_rq req;
	unsigned char rqdata[4];

	if (!p || !cmd) {
		lprintf(LOG_ERR, "_get_subfn_enables: p or cmd is NULL");
		return -1;
	}

	memset(&req, 0, sizeof(req));
	req.msg.netfn = IPMI_NETFN_APP;
	req.msg.cmd = BMC_GET_COMMAND_SUBFUNCTION_ENABLES;
	rqdata[0] = (unsigned char) p->channel;
	rqdata[1] = p->netfn;
	rqdata[2] = p->lun;
	rqdata[3] = p->command;
	req.msg.data = rqdata;
	req.msg.data_len = 4;

	rsp = intf->sendrecv(intf, &req);
	if (rsp == NULL) {
		lprintf(LOG_ERR, "Get Command Sub-function Enables (LUN=%d, NetFn=%d, command=%d) command failed", p->lun, p->netfn, p->command);
		return -1;
	}
	if (rsp->ccode > 0) {
		lprintf(LOG_ERR, "Get Command Sub-function Enables (LUN=%d, NetFn=%d, command=%d) command failed: %s",
			p->lun, p->netfn, p->command, val2str(rsp->ccode, completion_code_vals));
		return -1;
	}

	memcpy(cmd->subfn_enable, rsp->data, sizeof(cmd->subfn_enable));
	return 0;
}
