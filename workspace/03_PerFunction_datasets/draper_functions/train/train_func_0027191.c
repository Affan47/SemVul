ide_set_dev_param_mask(const char *s, const struct kernel_param *kp)
{
	int a, b, i, j = 1;
	unsigned int *dev_param_mask = (unsigned int *)kp->arg;


	if (sscanf(s, "%d.%d:%d", &a, &b, &j) != 3 &&
	    sscanf(s, "%d.%d", &a, &b) != 2)
		return -EINVAL;

	i = a * MAX_DRIVES + b;

	if (i >= MAX_HWIFS * MAX_DRIVES || j < 0 || j > 1)
		return -EINVAL;

	if (j)
		*dev_param_mask |= (1 << i);
	else
		*dev_param_mask &= ~(1 << i);

	return 0;
}
