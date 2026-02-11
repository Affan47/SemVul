autofs4_expire_multi(struct super_block *sb, struct vfsmount *mnt,
			struct autofs_sb_info *sbi, int __user *arg)
{
	int do_now = 0;

	if (arg && get_user(do_now, arg))
		return -EFAULT;

	return autofs4_do_expire_multi(sb, mnt, sbi, do_now);
}
