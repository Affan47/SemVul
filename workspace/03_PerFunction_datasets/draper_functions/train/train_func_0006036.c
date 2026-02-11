l3ni1_msg_with_uus(struct l3_process *pc, u_char cmd)
{
	struct sk_buff *skb;
	u_char tmp[16 + 40];
	u_char *p = tmp;
	int l;

	MsgHead(p, pc->callref, cmd);

	if (pc->prot.ni1.uus1_data[0])
	{ *p++ = IE_USER_USER;
		*p++ = strlen(pc->prot.ni1.uus1_data) + 1;
		*p++ = 0x04;
		strcpy(p, pc->prot.ni1.uus1_data);
		p += strlen(pc->prot.ni1.uus1_data);
		pc->prot.ni1.uus1_data[0] = '\0';
	}

	l = p - tmp;
	if (!(skb = l3_alloc_skb(l)))
		return;
	memcpy(skb_put(skb, l), tmp, l);
	l3_msg(pc->st, DL_DATA | REQUEST, skb);
}
