ipmi_tsol_command(struct ipmi_intf * intf, char *recvip, int port, unsigned char cmd)
{
        struct ipmi_rs *rsp;
        struct ipmi_rq	req;
        unsigned char	data[6];
	unsigned	ip1, ip2, ip3, ip4;

        if (sscanf(recvip, "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4) != 4) {
                lprintf(LOG_ERR, "Invalid IP address: %s", recvip);
                return -1;
        }

	memset(&req, 0, sizeof(struct ipmi_rq));
        req.msg.netfn    = IPMI_NETFN_TSOL;
        req.msg.cmd      = cmd;
        req.msg.data_len = 6;
        req.msg.data     = data;

	memset(data, 0, sizeof(data));
        data[0] = ip1;
        data[1] = ip2;
        data[2] = ip3;
        data[3] = ip4;
        data[4] = (port & 0xff00) >> 8;
        data[5] = (port & 0xff);

        rsp = intf->sendrecv(intf, &req);
        if (rsp == NULL) {
		lprintf(LOG_ERR, "Unable to perform TSOL command");
                return -1;
	}
	if (rsp->ccode > 0) {
		lprintf(LOG_ERR, "Unable to perform TSOL command: %s",
			val2str(rsp->ccode, completion_code_vals));
		return -1;
        }

        return 0;
}
