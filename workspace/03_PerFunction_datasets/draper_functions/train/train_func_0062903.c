alloc_sq(struct c4iw_rdev *rdev, struct t4_sq *sq, int user)
{
	int ret = -ENOSYS;
	if (user)
		ret = alloc_oc_sq(rdev, sq);
	if (ret)
		ret = alloc_host_sq(rdev, sq);
	return ret;
}
