l2_st5_persistent_da(struct FsmInst *fi, int event, void *arg)
{
	struct layer2 *l2 = fi->userdata;
	struct sk_buff *skb = arg;

	skb_queue_purge(&l2->i_queue);
	skb_queue_purge(&l2->ui_queue);
	freewin(l2);
	stop_t200(l2, 19);
	st5_dl_release_l2l3(l2);
	mISDN_FsmChangeState(fi, ST_L2_4);
	if (l2->tm)
		l2_tei(l2, MDL_STATUS_DOWN_IND, 0);
	dev_kfree_skb(skb);
}
