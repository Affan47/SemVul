dlm_lock_sync(struct dlm_lock_resource *res, int mode)
{
	int ret = 0;

	ret = dlm_lock(res->ls, mode, &res->lksb,
			res->flags, res->name, strlen(res->name),
			0, sync_ast, res, res->bast);
	if (ret)
		return ret;
	wait_for_completion(&res->completion);
	if (res->lksb.sb_status == 0)
		res->mode = mode;
	return res->lksb.sb_status;
}
