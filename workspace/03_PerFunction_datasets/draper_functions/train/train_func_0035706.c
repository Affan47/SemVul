ipath_get_slave_info(struct ipath_portdata *pd,
				void __user *slave_mask_addr)
{
	int ret = 0;

	if (copy_to_user(slave_mask_addr, &pd->active_slaves, sizeof(u32)))
		ret = -EFAULT;
	return ret;
}
