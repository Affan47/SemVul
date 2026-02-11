l3dss1_suspend_rej(struct l3_process *pc, u_char pr, void *arg)
{
	struct sk_buff *skb = arg;
	int ret;

	if ((ret = l3dss1_get_cause(pc, skb))) {
		if (pc->debug & L3_DEB_WARN)
			l3_debug(pc->st, "SUSP_REJ get_cause ret(%d)", ret);
		if (ret < 0)
			pc->para.cause = 96;
		else
			pc->para.cause = 100;
		l3dss1_status_send(pc, pr, NULL);
		return;
	}
	ret = check_infoelements(pc, skb, ie_SUSPEND_REJECT);
	if (ERR_IE_COMPREHENSION == ret) {
		l3dss1_std_ie_err(pc, ret);
		return;
	}
	L3DelTimer(&pc->timer);
	pc->st->l3.l3l4(pc->st, CC_SUSPEND_ERR, pc);
	newl3state(pc, 10);
	if (ret)
		l3dss1_std_ie_err(pc, ret);
}
