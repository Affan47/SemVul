l2_reestablish(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;
	struct sk_buff *skb = arg;

	if (!get_PollFlagFree(st, skb)) {
		establishlink(fi);
		test_and_set_bit(FLG_L3_INIT, &st->l2.flag);
	}
}
