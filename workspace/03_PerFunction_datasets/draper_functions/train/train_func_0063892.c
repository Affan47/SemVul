ide_setting_ioctl(ide_drive_t *drive, struct block_device *bdev,
		      unsigned int cmd, unsigned long arg,
		      const struct ide_ioctl_devset *s)
{
	const struct ide_devset *ds;
	int err = -EOPNOTSUPP;

	for (; (ds = s->setting); s++) {
		if (ds->get && s->get_ioctl == cmd)
			goto read_val;
		else if (ds->set && s->set_ioctl == cmd)
			goto set_val;
	}

	return err;

read_val:
	mutex_lock(&ide_setting_mtx);
	err = ds->get(drive);
	mutex_unlock(&ide_setting_mtx);
	return err >= 0 ? put_user(err, (long __user *)arg) : err;

set_val:
	if (bdev != bdev->bd_contains)
		err = -EINVAL;
	else {
		if (!capable(CAP_SYS_ADMIN))
			err = -EACCES;
		else {
			mutex_lock(&ide_setting_mtx);
			err = ide_devset_execute(drive, ds, arg);
			mutex_unlock(&ide_setting_mtx);
		}
	}
	return err;
}
