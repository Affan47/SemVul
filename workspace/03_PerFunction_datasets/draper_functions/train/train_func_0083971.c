send_close_req(struct cxgbi_sock *csk)
{
	struct sk_buff *skb = csk->cpl_close;
	struct cpl_close_con_req *req = (struct cpl_close_con_req *)skb->head;
	unsigned int tid = csk->tid;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx, tid %u.\n",
		csk, csk->state, csk->flags, csk->tid);
	csk->cpl_close = NULL;
	set_wr_txq(skb, CPL_PRIORITY_DATA, csk->port_id);
	INIT_TP_WR(req, tid);
	OPCODE_TID(req) = cpu_to_be32(MK_OPCODE_TID(CPL_CLOSE_CON_REQ, tid));
	req->rsvd = 0;

	cxgbi_sock_skb_entail(csk, skb);
	if (csk->state >= CTP_ESTABLISHED)
		push_tx_frames(csk, 1);
}
