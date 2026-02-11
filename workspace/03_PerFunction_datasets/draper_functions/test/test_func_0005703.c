l3dss1_redir_req(struct l3_process *pc, u_char pr, void *arg)
{
	struct sk_buff *skb;
	u_char tmp[128];
	u_char *p = tmp;
	u_char *subp;
	u_char len_phone = 0;
	u_char len_sub = 0;
	int l;


	strcpy(pc->prot.dss1.uus1_data, pc->chan->setup.eazmsn);
	if (!pc->chan->setup.phone[0])
	{ pc->para.cause = -1;
		l3dss1_disconnect_req(pc, pr, arg);
		return;
	}

	if (pc->prot.dss1.invoke_id)
		free_invoke_id(pc->st, pc->prot.dss1.invoke_id);

	if (!(pc->prot.dss1.invoke_id = new_invoke_id(pc->st)))
		return;

	MsgHead(p, pc->callref, MT_FACILITY);

	for (subp = pc->chan->setup.phone; (*subp) && (*subp != '.'); subp++) len_phone++;
	if (*subp++ == '.') len_sub = strlen(subp) + 2;

	*p++ = 0x1c;
	*p++ = len_phone + len_sub + 2 + 2 + 8 + 3 + 3;
	*p++ = 0x91;
	*p++ = 0xa1;

	*p++ = len_phone + len_sub + 2 + 2 + 8 + 3;
	*p++ = 0x02;
	*p++ = 0x01;
	*p++ = pc->prot.dss1.invoke_id;
	*p++ = 0x02;
	*p++ = 0x01;
	*p++ = 0x0D;

	*p++ = 0x30;
	*p++ = len_phone + 2 + 2 + 3 + len_sub;

	*p++ = 0x30;
	*p++ = len_phone + 2 + len_sub;
	*p++ = 0x80;
	*p++ = len_phone;
	for (l = 0; l < len_phone; l++)
		*p++ = pc->chan->setup.phone[l];

	if (len_sub)
	{ *p++ = 0x04;
		*p++ = len_sub - 2;
		while (*subp) *p++ = *subp++;
	}

	*p++ = 0x01;
	*p++ = 0x01;
	*p++ = pc->chan->setup.screen;

	l = p - tmp;
	if (!(skb = l3_alloc_skb(l))) return;
	memcpy(skb_put(skb, l), tmp, l);

	l3_msg(pc->st, DL_DATA | REQUEST, skb);
}
