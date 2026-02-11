do_abort_req_rss(struct t3cdev *dev, struct sk_buff *skb)
{
	union opcode_tid *p = cplhdr(skb);
	unsigned int hwtid = G_TID(ntohl(p->opcode_tid));
	struct t3c_tid_entry *t3c_tid;

	t3c_tid = lookup_tid(&(T3C_DATA(dev))->tid_maps, hwtid);
	if (t3c_tid && t3c_tid->ctx && t3c_tid->client->handlers &&
	    t3c_tid->client->handlers[p->opcode]) {
		return t3c_tid->client->handlers[p->opcode]
		    (dev, skb, t3c_tid->ctx);
	} else {
		struct cpl_abort_req_rss *req = cplhdr(skb);
		struct cpl_abort_rpl *rpl;
		struct sk_buff *reply_skb;
		unsigned int tid = GET_TID(req);
		u8 cmd = req->status;

		if (req->status == CPL_ERR_RTX_NEG_ADVICE ||
		    req->status == CPL_ERR_PERSIST_NEG_ADVICE)
			goto out;

		reply_skb = cxgb3_get_cpl_reply_skb(skb,
						    sizeof(struct
							   cpl_abort_rpl),
						    GFP_ATOMIC);

		if (!reply_skb) {
			printk("do_abort_req_rss: couldn't get skb!\n");
			goto out;
		}
		reply_skb->priority = CPL_PRIORITY_DATA;
		__skb_put(reply_skb, sizeof(struct cpl_abort_rpl));
		rpl = cplhdr(reply_skb);
		rpl->wr.wr_hi =
		    htonl(V_WR_OP(FW_WROPCODE_OFLD_HOST_ABORT_CON_RPL));
		rpl->wr.wr_lo = htonl(V_WR_TID(tid));
		OPCODE_TID(rpl) = htonl(MK_OPCODE_TID(CPL_ABORT_RPL, tid));
		rpl->cmd = cmd;
		cxgb3_ofld_send(dev, reply_skb);
out:
		return CPL_RET_BUF_DONE;
	}
}
