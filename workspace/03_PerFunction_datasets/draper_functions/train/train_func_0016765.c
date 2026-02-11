l2_released(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;
	struct sk_buff *skb = arg;

	if (!get_PollFlag(st, skb)) {
		l2_mdl_error_ua(fi, event, arg);
		return;
	}
	dev_kfree_skb(skb);

	stop_t200(st, 6);
	lapb_dl_release_l2l3(st, CONFIRM);
	FsmChangeState(fi, ST_L2_4);
}
