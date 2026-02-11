l2_st5_tout_200(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;

	if (test_bit(FLG_LAPD, &st->l2.flag) &&
	    test_bit(FLG_DCHAN_BUSY, &st->l2.flag)) {
		FsmAddTimer(&st->l2.t200, st->l2.T200, EV_L2_T200, NULL, 9);
	} else if (st->l2.rc == st->l2.N200) {
		FsmChangeState(fi, ST_L2_4);
		test_and_clear_bit(FLG_T200_RUN, &st->l2.flag);
		skb_queue_purge(&st->l2.i_queue);
		st->ma.layer(st, MDL_ERROR | INDICATION, (void *) 'G');
		if (test_bit(FLG_LAPB, &st->l2.flag))
			st->l2.l2l1(st, PH_DEACTIVATE | REQUEST, NULL);
		st5_dl_release_l2l3(st);
	} else {
		st->l2.rc++;
		FsmAddTimer(&st->l2.t200, st->l2.T200, EV_L2_T200, NULL, 9);
		send_uframe(st, (test_bit(FLG_MOD128, &st->l2.flag) ? SABME : SABM)
			    | 0x10, CMD);
	}
}
