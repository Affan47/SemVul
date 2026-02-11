arenas_narenas_ctl(const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen)
{
	int ret;
	unsigned narenas;

	malloc_mutex_lock(&ctl_mtx);
	READONLY();
	if (*oldlenp != sizeof(unsigned)) {
		ret = EINVAL;
		goto label_return;
	}
	narenas = ctl_stats.narenas;
	READ(narenas, unsigned);

	ret = 0;
label_return:
	malloc_mutex_unlock(&ctl_mtx);
	return (ret);
}
