l2_got_ui(struct FsmInst *fi, int event, void *arg)
{
	struct layer2 *l2 = fi->userdata;
	struct sk_buff *skb = arg;

	skb_pull(skb, l2headersize(l2, 1));


	if (l2->tm)
		l2_tei(l2, MDL_STATUS_UI_IND, 0);
	l2up(l2, DL_UNITDATA_IND, skb);
}
