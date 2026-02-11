epoch_ctl(const size_t *mib, size_t miblen, void *oldp, size_t *oldlenp,
    void *newp, size_t newlen)
{
	int ret;
	uint64_t newval;

	malloc_mutex_lock(&ctl_mtx);
	newval = 0;
	WRITE(newval, uint64_t);
	if (newval != 0)
		ctl_refresh();
	READ(ctl_epoch, uint64_t);

	ret = 0;
RETURN:
	malloc_mutex_unlock(&ctl_mtx);
	return (ret);
}
