quota_sync_store(struct gfs2_sbd *sdp, const char *buf,
				size_t len)
{
	int error, val;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	error = kstrtoint(buf, 0, &val);
	if (error)
		return error;

	if (val != 1)
		return -EINVAL;

	gfs2_quota_sync(sdp->sd_vfs, 0);
	return len;
}
