set_param_timeout(const char *val, const struct kernel_param *kp)
{
	char *endp;
	int  l;
	int  rv = 0;

	if (!val)
		return -EINVAL;
	l = simple_strtoul(val, &endp, 0);
	if (endp == val)
		return -EINVAL;

	*((int *)kp->arg) = l;
	if (watchdog_user)
		rv = ipmi_set_timeout(IPMI_SET_TIMEOUT_HB_IF_NECESSARY);

	return rv;
}
