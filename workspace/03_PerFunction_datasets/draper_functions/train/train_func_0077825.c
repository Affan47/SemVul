convert_lock(struct dlm_ls *ls, struct dlm_lkb *lkb,
			struct dlm_args *args)
{
	struct dlm_rsb *r;
	int error;

	r = lkb->lkb_resource;

	hold_rsb(r);
	lock_rsb(r);

	error = validate_lock_args(ls, lkb, args);
	if (error)
		goto out;

	error = _convert_lock(r, lkb);
 out:
	unlock_rsb(r);
	put_rsb(r);
	return error;
}
