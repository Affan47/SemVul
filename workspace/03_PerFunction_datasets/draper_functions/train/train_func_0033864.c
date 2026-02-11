l2_got_FRMR(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;
	struct sk_buff *skb = arg;

	skb_pull(skb, l2addrsize(&st->l2) + 1);

	if (!(skb->data[0] & 1) || ((skb->data[0] & 3) == 1) ||
	    (IsUA(skb->data) && (fi->state == ST_L2_7))) {
		st->ma.layer(st, MDL_ERROR | INDICATION, (void *) 'K');
		establishlink(fi);
		test_and_clear_bit(FLG_L3_INIT, &st->l2.flag);
	}
	dev_kfree_skb(skb);
}
