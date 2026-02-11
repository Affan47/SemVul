tune_set(struct gfs2_sbd *sdp, unsigned int *field,
			int check_zero, const char *buf, size_t len)
{
	struct gfs2_tune *gt = &sdp->sd_tune;
	unsigned int x;
	int error;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	error = kstrtouint(buf, 0, &x);
	if (error)
		return error;

	if (check_zero && !x)
		return -EINVAL;

	spin_lock(&gt->gt_spin);
	*field = x;
	spin_unlock(&gt->gt_spin);
	return len;
}
