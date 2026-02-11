failed_resolver(uint16_t xid)
{
	struct dnsreq *req;

	req = &querytable[xid];
	if(req->callback == NULL)
		return;

	req->callback("FAILED", 0, 0, req->data);
	req->callback = NULL;
	req->data = NULL;
}
