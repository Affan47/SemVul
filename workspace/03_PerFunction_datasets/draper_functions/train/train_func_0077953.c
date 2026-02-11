recover_lvb(struct dlm_rsb *r)
{
	struct dlm_lkb *lkb, *high_lkb = NULL;
	uint32_t high_seq = 0;
	int lock_lvb_exists = 0;
	int big_lock_exists = 0;
	int lvblen = r->res_ls->ls_lvblen;

	if (!rsb_flag(r, RSB_NEW_MASTER2) &&
	    rsb_flag(r, RSB_RECOVER_LVB_INVAL)) {

		rsb_set_flag(r, RSB_VALNOTVALID);
		return;
	}

	if (!rsb_flag(r, RSB_NEW_MASTER2))
		return;


	list_for_each_entry(lkb, &r->res_grantqueue, lkb_statequeue) {
		if (!(lkb->lkb_exflags & DLM_LKF_VALBLK))
			continue;

		lock_lvb_exists = 1;

		if (lkb->lkb_grmode > DLM_LOCK_CR) {
			big_lock_exists = 1;
			goto setflag;
		}

		if (((int)lkb->lkb_lvbseq - (int)high_seq) >= 0) {
			high_lkb = lkb;
			high_seq = lkb->lkb_lvbseq;
		}
	}

	list_for_each_entry(lkb, &r->res_convertqueue, lkb_statequeue) {
		if (!(lkb->lkb_exflags & DLM_LKF_VALBLK))
			continue;

		lock_lvb_exists = 1;

		if (lkb->lkb_grmode > DLM_LOCK_CR) {
			big_lock_exists = 1;
			goto setflag;
		}

		if (((int)lkb->lkb_lvbseq - (int)high_seq) >= 0) {
			high_lkb = lkb;
			high_seq = lkb->lkb_lvbseq;
		}
	}

 setflag:
	if (!lock_lvb_exists)
		goto out;


	if (!big_lock_exists)
		rsb_set_flag(r, RSB_VALNOTVALID);

	if (!r->res_lvbptr) {
		r->res_lvbptr = dlm_allocate_lvb(r->res_ls);
		if (!r->res_lvbptr)
			goto out;
	}

	if (big_lock_exists) {
		r->res_lvbseq = lkb->lkb_lvbseq;
		memcpy(r->res_lvbptr, lkb->lkb_lvbptr, lvblen);
	} else if (high_lkb) {
		r->res_lvbseq = high_lkb->lkb_lvbseq;
		memcpy(r->res_lvbptr, high_lkb->lkb_lvbptr, lvblen);
	} else {
		r->res_lvbseq = 0;
		memset(r->res_lvbptr, 0, lvblen);
	}
 out:
	return;
}
