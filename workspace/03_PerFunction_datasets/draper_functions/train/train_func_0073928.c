cxgb3_alloc_stid(struct t3cdev *tdev, struct cxgb3_client *client,
		     void *ctx)
{
	int stid = -1;
	struct tid_info *t = &(T3C_DATA(tdev))->tid_maps;

	spin_lock_bh(&t->stid_lock);
	if (t->sfree) {
		union listen_entry *p = t->sfree;

		stid = (p - t->stid_tab) + t->stid_base;
		t->sfree = p->next;
		p->t3c_tid.ctx = ctx;
		p->t3c_tid.client = client;
		t->stids_in_use++;
	}
	spin_unlock_bh(&t->stid_lock);
	return stid;
}
