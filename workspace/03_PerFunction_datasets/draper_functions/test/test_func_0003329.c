uwb_rc_neh_create(struct uwb_rc *rc)
{
	spin_lock_init(&rc->neh_lock);
	INIT_LIST_HEAD(&rc->neh_list);
	set_bit(0, rc->ctx_bm);
	set_bit(0xff, rc->ctx_bm);
	rc->ctx_roll = 1;
}
