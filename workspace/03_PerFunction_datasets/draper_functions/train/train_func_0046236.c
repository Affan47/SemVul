dlm_user_cancel(struct dlm_ls *ls, struct dlm_user_args *ua_tmp,
		    uint32_t flags, uint32_t lkid)
{
	struct dlm_lkb *lkb;
	struct dlm_args args;
	struct dlm_user_args *ua;
	int error;

	dlm_lock_recovery(ls);

	error = find_lkb(ls, lkid, &lkb);
	if (error)
		goto out;

	ua = lkb->lkb_ua;
	if (ua_tmp->castparam)
		ua->castparam = ua_tmp->castparam;
	ua->user_lksb = ua_tmp->user_lksb;

	error = set_unlock_args(flags, ua, &args);
	if (error)
		goto out_put;

	error = cancel_lock(ls, lkb, &args);

	if (error == -DLM_ECANCEL)
		error = 0;

	if (error == -EBUSY)
		error = 0;
 out_put:
	dlm_put_lkb(lkb);
 out:
	dlm_unlock_recovery(ls);
	kfree(ua_tmp);
	return error;
}
