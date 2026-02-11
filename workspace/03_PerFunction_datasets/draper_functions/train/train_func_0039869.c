iwch_post_terminate(struct iwch_qp *qhp, struct respQ_msg_t *rsp_msg)
{
	union t3_wr *wqe;
	struct terminate_message *term;
	struct sk_buff *skb;

	PDBG("%s %d\n", __func__, __LINE__);
	skb = alloc_skb(40, GFP_ATOMIC);
	if (!skb) {
		printk(KERN_ERR "%s cannot send TERMINATE!\n", __func__);
		return -ENOMEM;
	}
	wqe = (union t3_wr *)skb_put(skb, 40);
	memset(wqe, 0, 40);
	wqe->send.rdmaop = T3_TERMINATE;


	wqe->send.plen = htonl(4);


	term = (struct terminate_message *)wqe->send.sgl;
	build_term_codes(rsp_msg, &term->layer_etype, &term->ecode);
	wqe->send.wrh.op_seop_flags = cpu_to_be32(V_FW_RIWR_OP(T3_WR_SEND) |
			 V_FW_RIWR_FLAGS(T3_COMPLETION_FLAG | T3_NOTIFY_FLAG));
	wqe->send.wrh.gen_tid_len = cpu_to_be32(V_FW_RIWR_TID(qhp->ep->hwtid));
	skb->priority = CPL_PRIORITY_DATA;
	return iwch_cxgb3_ofld_send(qhp->rhp->rdev.t3cdev_p, skb);
}
