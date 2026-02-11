nilfs_ioctl_get_cpstat(struct inode *inode, struct file *filp,
				  unsigned int cmd, void __user *argp)
{
	struct the_nilfs *nilfs = inode->i_sb->s_fs_info;
	struct nilfs_cpstat cpstat;
	int ret;

	down_read(&nilfs->ns_segctor_sem);
	ret = nilfs_cpfile_get_stat(nilfs->ns_cpfile, &cpstat);
	up_read(&nilfs->ns_segctor_sem);
	if (ret < 0)
		return ret;

	if (copy_to_user(argp, &cpstat, sizeof(cpstat)))
		ret = -EFAULT;
	return ret;
}
