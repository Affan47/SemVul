l3dss1_status(struct l3_process *pc, u_char pr, void *arg)
{
	u_char *p;
	struct sk_buff *skb = arg;
	int ret;
	u_char cause = 0, callState = 0;

	if ((ret = l3dss1_get_cause(pc, skb))) {
		if (pc->debug & L3_DEB_WARN)
			l3_debug(pc->st, "STATUS get_cause ret(%d)", ret);
		if (ret < 0)
			cause = 96;
		else if (ret > 0)
			cause = 100;
	}
	if ((p = findie(skb->data, skb->len, IE_CALL_STATE, 0))) {
		p++;
		if (1 == *p++) {
			callState = *p;
			if (!ie_in_set(pc, *p, l3_valid_states))
				cause = 100;
		} else
			cause = 100;
	} else
		cause = 96;
	if (!cause) {
		ret = check_infoelements(pc, skb, ie_STATUS);
		if (ERR_IE_COMPREHENSION == ret)
			cause = 96;
		else if (ERR_IE_UNRECOGNIZED == ret)
			cause = 99;
	}
	if (cause) {
		u_char tmp;

		if (pc->debug & L3_DEB_WARN)
			l3_debug(pc->st, "STATUS error(%d/%d)", ret, cause);
		tmp = pc->para.cause;
		pc->para.cause = cause;
		l3dss1_status_send(pc, 0, NULL);
		if (cause == 99)
			pc->para.cause = tmp;
		else
			return;
	}
	cause = pc->para.cause;
	if (((cause & 0x7f) == 111) && (callState == 0)) {


		pc->st->l3.l3l4(pc->st, CC_RELEASE | INDICATION, pc);
		newl3state(pc, 0);
		dss1_release_l3_process(pc);
	}
}
