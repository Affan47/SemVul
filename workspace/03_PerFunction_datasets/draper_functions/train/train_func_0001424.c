l3dss1_release(struct l3_process *pc, u_char pr, void *arg)
{
	struct sk_buff *skb = arg;
	u_char *p;
	int ret, cause = 0;

	StopAllL3Timer(pc);
	if ((ret = l3dss1_get_cause(pc, skb)) > 0) {
		if (pc->debug & L3_DEB_WARN)
			l3_debug(pc->st, "REL get_cause ret(%d)", ret);
	} else if (ret < 0)
		pc->para.cause = NO_CAUSE;
	if ((p = findie(skb->data, skb->len, IE_FACILITY, 0))) {
		l3dss1_parse_facility(pc->st, pc, pc->callref, p);
	}
	if ((ret < 0) && (pc->state != 11))
		cause = 96;
	else if (ret > 0)
		cause = 100;
	ret = check_infoelements(pc, skb, ie_RELEASE);
	if (ERR_IE_COMPREHENSION == ret)
		cause = 96;
	else if ((ERR_IE_UNRECOGNIZED == ret) && (!cause))
		cause = 99;
	if (cause)
		l3dss1_message_cause(pc, MT_RELEASE_COMPLETE, cause);
	else
		l3dss1_message(pc, MT_RELEASE_COMPLETE);
	pc->st->l3.l3l4(pc->st, CC_RELEASE | INDICATION, pc);
	newl3state(pc, 0);
	dss1_release_l3_process(pc);
}
