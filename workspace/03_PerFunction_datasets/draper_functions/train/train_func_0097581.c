l2_feed_i_if_reest(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;
	struct sk_buff *skb = arg;

	if (test_bit(FLG_LAPB, &st->l2.flag))
		st->l1.bcs->tx_cnt += skb->len + l2headersize(&st->l2, 0);
	if (!test_bit(FLG_L3_INIT, &st->l2.flag))
		skb_queue_tail(&st->l2.i_queue, skb);
	else
		dev_kfree_skb(skb);
}
