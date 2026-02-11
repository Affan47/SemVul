lockres_free(struct dlm_lock_resource *res)
{
	int ret;

	if (!res)
		return;


	res->flags |= DLM_LKF_CANCEL;
retry:
	ret = dlm_unlock(res->ls, res->lksb.sb_lkid, 0, &res->lksb, res);
	if (unlikely(ret != 0)) {
		pr_info("%s: failed to unlock %s return %d\n", __func__, res->name, ret);


		if (ret == -DLM_ECANCEL)
			goto retry;
	}
	res->flags &= ~DLM_LKF_CANCEL;
	wait_for_completion(&res->completion);

	kfree(res->name);
	kfree(res->lksb.sb_lvbptr);
	kfree(res);
}
