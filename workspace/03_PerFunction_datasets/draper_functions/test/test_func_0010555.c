grant_pending_locks(struct dlm_rsb *r, unsigned int *count)
{
	struct dlm_lkb *lkb, *s;
	int high = DLM_LOCK_IV;
	int cw = 0;

	if (!is_master(r)) {
		log_print("grant_pending_locks r nodeid %d", r->res_nodeid);
		dlm_dump_rsb(r);
		return;
	}

	high = grant_pending_convert(r, high, &cw, count);
	high = grant_pending_wait(r, high, &cw, count);

	if (high == DLM_LOCK_IV)
		return;


	list_for_each_entry_safe(lkb, s, &r->res_grantqueue, lkb_statequeue) {
		if (lkb->lkb_bastfn && lock_requires_bast(lkb, high, cw)) {
			if (cw && high == DLM_LOCK_PR &&
			    lkb->lkb_grmode == DLM_LOCK_PR)
				queue_bast(r, lkb, DLM_LOCK_CW);
			else
				queue_bast(r, lkb, high);
			lkb->lkb_highbast = high;
		}
	}
}
