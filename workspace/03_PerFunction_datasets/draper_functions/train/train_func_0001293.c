pt_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct pt_unit *tape = file->private_data;
	struct mtop __user *p = (void __user *)arg;
	struct mtop mtop;

	switch (cmd) {
	case MTIOCTOP:
		if (copy_from_user(&mtop, p, sizeof(struct mtop)))
			return -EFAULT;

		switch (mtop.mt_op) {

		case MTREW:
			mutex_lock(&pt_mutex);
			pt_rewind(tape);
			mutex_unlock(&pt_mutex);
			return 0;

		case MTWEOF:
			mutex_lock(&pt_mutex);
			pt_write_fm(tape);
			mutex_unlock(&pt_mutex);
			return 0;

		default:

			printk(KERN_DEBUG "%s: Unimplemented mt_op %d\n", tape->name,
			       mtop.mt_op);
			return -EINVAL;
		}

	default:
		return -ENOTTY;
	}
}
