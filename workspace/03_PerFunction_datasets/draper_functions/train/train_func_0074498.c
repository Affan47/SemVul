ipmi_req_add_entry(struct ipmi_intf * intf, struct ipmi_rq * req)
{
	struct ipmi_rq_entry * e;

	e = malloc(sizeof(struct ipmi_rq_entry));
	if (e == NULL) {
		lprintf(LOG_ERR, "ipmitool: malloc failure");
		return NULL;
	}

	memset(e, 0, sizeof(struct ipmi_rq_entry));
	memcpy(&e->req, req, sizeof(struct ipmi_rq));

	e->intf = intf;

	if (ipmi_req_entries == NULL)
		ipmi_req_entries = e;
	else
		ipmi_req_entries_tail->next = e;

	ipmi_req_entries_tail = e;
	lprintf(LOG_DEBUG+3, "added list entry seq=0x%02x cmd=0x%02x",
		e->rq_seq, e->req.msg.cmd);
	return e;
}
