keypad_open(struct inode *inode, struct file *file)
{
	int ret;

	ret = -EBUSY;
	if (!atomic_dec_and_test(&keypad_available))
		goto fail;

	ret = -EPERM;
	if (file->f_mode & FMODE_WRITE)
		goto fail;

	keypad_buflen = 0;
	return 0;
 fail:
	atomic_inc(&keypad_available);
	return ret;
}
