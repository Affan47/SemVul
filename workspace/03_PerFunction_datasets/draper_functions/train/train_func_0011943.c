abort_arp_failure(void *handle, struct sk_buff *skb)
{
	struct cxgbi_sock *csk = (struct cxgbi_sock *)handle;
	struct cpl_abort_req *req;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx, tid %u, abort.\n",
		csk, csk->state, csk->flags, csk->tid);
	req = (struct cpl_abort_req *)skb->data;
	req->cmd = CPL_ABORT_NO_RST;
	cxgb4_ofld_send(csk->cdev->ports[csk->port_id], skb);
}
