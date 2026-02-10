ls_unlock_v6(struct dlm_ls_info *lsinfo, uint32_t lkid,
			uint32_t flags, struct dlm_lksb *lksb, void *astarg)
{
	struct dlm_write_request req;

	set_version_v6(&req);
	req.cmd = DLM_USER_UNLOCK;
	req.i.lock.lkid = lkid;
	req.i.lock.flags = (flags & ~LKF_WAIT);
	req.i.lock.lksb  = lksb;
	req.i.lock.namelen = 0;
	req.i.lock.castparam = astarg;

	req.i.lock.castaddr = 0;
	lksb->sb_status = EINPROG;

	if (flags & LKF_WAIT)
		return sync_write_v6(lsinfo, &req, sizeof(req));
	else
		return write(lsinfo->fd, &req, sizeof(req));
}
