l2_restart_multi(struct FsmInst *fi, int event, void *arg)
{
	struct layer2	*l2 = fi->userdata;
	struct sk_buff	*skb = arg;
	int		est = 0;

	send_uframe(l2, skb, UA | get_PollFlag(l2, skb), RSP);

	l2mgr(l2, MDL_ERROR_IND, (void *) 'F');

	if (l2->vs != l2->va) {
		skb_queue_purge(&l2->i_queue);
		est = 1;
	}

	clear_exception(l2);
	l2->vs = 0;
	l2->va = 0;
	l2->vr = 0;
	l2->sow = 0;
	mISDN_FsmChangeState(fi, ST_L2_7);
	stop_t200(l2, 3);
	mISDN_FsmRestartTimer(&l2->t203, l2->T203, EV_L2_T203, NULL, 3);

	if (est)
		l2up_create(l2, DL_ESTABLISH_IND, 0, NULL);


	if (skb_queue_len(&l2->i_queue) && cansend(l2))
		mISDN_FsmEvent(fi, EV_L2_ACK_PULL, NULL);
}
