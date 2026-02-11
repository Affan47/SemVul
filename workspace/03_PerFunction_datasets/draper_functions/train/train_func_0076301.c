do_stid_rpl(struct t3cdev *dev, struct sk_buff *skb)
{
	union opcode_tid *p = cplhdr(skb);
	unsigned int stid = G_TID(ntohl(p->opcode_tid));
	struct t3c_tid_entry *t3c_tid;

	t3c_tid = lookup_stid(&(T3C_DATA(dev))->tid_maps, stid);
	if (t3c_tid && t3c_tid->ctx && t3c_tid->client->handlers &&
	    t3c_tid->client->handlers[p->opcode]) {
		return t3c_tid->client->handlers[p->opcode] (dev, skb,
							     t3c_tid->ctx);
	} else {
		pr_err("%s: received clientless CPL command 0x%x\n",
		       dev->name, p->opcode);
		return CPL_RET_BUF_DONE | CPL_RET_BAD_MSG;
	}
}
