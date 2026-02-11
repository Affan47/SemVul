release_l1(struct layer1 *l1) {
	mISDN_FsmDelTimer(&l1->timerX, 0);
	mISDN_FsmDelTimer(&l1->timer3, 0);
	if (l1->dch)
		l1->dch->l1 = NULL;
	module_put(THIS_MODULE);
	kfree(l1);
}
