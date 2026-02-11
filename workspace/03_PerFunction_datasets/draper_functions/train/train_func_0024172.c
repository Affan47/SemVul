l3ni1_SendSpid(struct l3_process *pc, u_char pr, struct sk_buff *skb, int iNewState)
{
	u_char *p;
	char *pSPID;
	struct Channel *pChan = pc->st->lli.userdata;
	int l;

	if (skb)
		dev_kfree_skb(skb);

	if (!(pSPID = strchr(pChan->setup.eazmsn, ':')))
	{
		printk(KERN_ERR "SPID not supplied in EAZMSN %s\n", pChan->setup.eazmsn);
		newl3state(pc, 0);
		pc->st->l3.l3l2(pc->st, DL_RELEASE | REQUEST, NULL);
		return;
	}

	l = strlen(++pSPID);
	if (!(skb = l3_alloc_skb(5 + l)))
	{
		printk(KERN_ERR "HiSax can't get memory to send SPID\n");
		return;
	}

	p = skb_put(skb, 5);
	*p++ = PROTO_DIS_EURO;
	*p++ = 0;
	*p++ = MT_INFORMATION;
	*p++ = IE_SPID;
	*p++ = l;

	memcpy(skb_put(skb, l), pSPID, l);

	newl3state(pc, iNewState);

	L3DelTimer(&pc->timer);
	L3AddTimer(&pc->timer, TSPID, CC_TSPID);

	pc->st->l3.l3l2(pc->st, DL_DATA | REQUEST, skb);
}
