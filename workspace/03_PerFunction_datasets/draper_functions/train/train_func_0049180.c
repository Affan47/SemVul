param_set_portnr(const char *val, const struct kernel_param *kp)
{
	unsigned long num;
	int ret;

	if (!val)
		return -EINVAL;
	ret = kstrtoul(val, 0, &num);
	if (ret == -EINVAL || num > NFS_CALLBACK_MAXPORTNR)
		return -EINVAL;
	*((unsigned int *)kp->arg) = num;
	return 0;
}
