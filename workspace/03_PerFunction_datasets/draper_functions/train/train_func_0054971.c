quota_getxstatev(struct super_block *sb, void __user *addr)
{
	struct fs_quota_statv fqs;
	int ret;

	if (!sb->s_qcop->get_state)
		return -ENOSYS;

	memset(&fqs, 0, sizeof(fqs));
	if (copy_from_user(&fqs, addr, 1))
		return -EFAULT;


	switch (fqs.qs_version) {
	case FS_QSTATV_VERSION1:
		break;
	default:
		return -EINVAL;
	}
	ret = quota_getstatev(sb, &fqs);
	if (!ret && copy_to_user(addr, &fqs, sizeof(fqs)))
		return -EFAULT;
	return ret;
}
