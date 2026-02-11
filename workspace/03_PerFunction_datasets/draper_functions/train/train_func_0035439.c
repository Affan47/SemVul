quota_getfmt(struct super_block *sb, int type, void __user *addr)
{
	__u32 fmt;

	mutex_lock(&sb_dqopt(sb)->dqonoff_mutex);
	if (!sb_has_quota_active(sb, type)) {
		mutex_unlock(&sb_dqopt(sb)->dqonoff_mutex);
		return -ESRCH;
	}
	fmt = sb_dqopt(sb)->info[type].dqi_format->qf_fmt_id;
	mutex_unlock(&sb_dqopt(sb)->dqonoff_mutex);
	if (copy_to_user(addr, &fmt, sizeof(fmt)))
		return -EFAULT;
	return 0;
}
