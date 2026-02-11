tei_id_chk_req_net(struct FsmInst *fi, int event, void *arg)
{
	struct teimgr	*tm = fi->userdata;

	if (*debug & DEBUG_L2_TEI)
		tm->tei_m.printdebug(fi, "id check request for tei %d",
				     tm->l2->tei);
	tm->rcnt = 0;
	put_tei_msg(tm->mgr, ID_CHK_REQ, 0, tm->l2->tei);
	mISDN_FsmChangeState(&tm->tei_m, ST_TEI_IDVERIFY);
	mISDN_FsmAddTimer(&tm->timer, tm->tval, EV_TIMER, NULL, 2);
	tm->nval = 2;
}
