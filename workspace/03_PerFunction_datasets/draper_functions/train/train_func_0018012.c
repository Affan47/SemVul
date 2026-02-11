send_rx_credits(struct cxgbi_sock *csk, u32 credits)
{
	struct sk_buff *skb;
	struct cpl_rx_data_ack *req;
	u32 dack = F_RX_DACK_CHANGE | V_RX_DACK_MODE(1);

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_RX,
		"csk 0x%p,%u,0x%lx,%u, credit %u, dack %u.\n",
		csk, csk->state, csk->flags, csk->tid, credits, dack);

	skb = alloc_wr(sizeof(*req), 0, GFP_ATOMIC);
	if (!skb) {
		pr_info("csk 0x%p, credit %u, OOM.\n", csk, credits);
		return 0;
	}
	req = (struct cpl_rx_data_ack *)skb->head;
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_RX_DATA_ACK, csk->tid));
	req->credit_dack = htonl(F_RX_DACK_CHANGE | V_RX_DACK_MODE(1) |
				V_RX_CREDITS(credits));
	skb->priority = CPL_PRIORITY_ACK;
	cxgb3_ofld_send(csk->cdev->lldev, skb);
	return credits;
}
