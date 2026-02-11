get_stats(struct slgt_info *info, struct mgsl_icount __user *user_icount)
{
	DBGINFO(("%s get_stats\n",  info->device_name));
	if (!user_icount) {
		memset(&info->icount, 0, sizeof(info->icount));
	} else {
		if (copy_to_user(user_icount, &info->icount, sizeof(struct mgsl_icount)))
			return -EFAULT;
	}
	return 0;
}
