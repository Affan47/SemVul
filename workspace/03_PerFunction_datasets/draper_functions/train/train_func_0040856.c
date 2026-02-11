l3_1tr6_connect(struct l3_process *pc, u_char pr, void *arg)
{
	struct sk_buff *skb = arg;

	L3DelTimer(&pc->timer);
	if (!findie(skb->data, skb->len, WE6_date, 6)) {
		l3_1tr6_error(pc, "missing connect date", skb);
		return;
	}
	newl3state(pc, 10);
	dev_kfree_skb(skb);
	pc->para.chargeinfo = 0;
	pc->st->l3.l3l4(pc->st, CC_SETUP | CONFIRM, pc);
}
