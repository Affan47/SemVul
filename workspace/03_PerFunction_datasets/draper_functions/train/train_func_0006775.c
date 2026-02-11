mtdchar_open(struct inode *inode, struct file *file)
{
	int minor = iminor(inode);
	int devnum = minor >> 1;
	int ret = 0;
	struct mtd_info *mtd;
	struct mtd_file_info *mfi;

	pr_debug("MTD_open\n");


	if ((file->f_mode & FMODE_WRITE) && (minor & 1))
		return -EACCES;

	mutex_lock(&mtd_mutex);
	mtd = get_mtd_device(NULL, devnum);

	if (IS_ERR(mtd)) {
		ret = PTR_ERR(mtd);
		goto out;
	}

	if (mtd->type == MTD_ABSENT) {
		ret = -ENODEV;
		goto out1;
	}


	if ((file->f_mode & FMODE_WRITE) && !(mtd->flags & MTD_WRITEABLE)) {
		ret = -EACCES;
		goto out1;
	}

	mfi = kzalloc(sizeof(*mfi), GFP_KERNEL);
	if (!mfi) {
		ret = -ENOMEM;
		goto out1;
	}
	mfi->mtd = mtd;
	file->private_data = mfi;
	mutex_unlock(&mtd_mutex);
	return 0;

out1:
	put_mtd_device(mtd);
out:
	mutex_unlock(&mtd_mutex);
	return ret;
}
