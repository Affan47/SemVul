lirc_dev_fop_open(struct inode *inode, struct file *file)
{
	struct irctl *ir;
	struct cdev *cdev;
	int retval = 0;

	if (iminor(inode) >= MAX_IRCTL_DEVICES) {
		printk(KERN_WARNING "lirc_dev [%d]: open result = -ENODEV\n",
		       iminor(inode));
		return -ENODEV;
	}

	if (mutex_lock_interruptible(&lirc_dev_lock))
		return -ERESTARTSYS;

	ir = irctls[iminor(inode)];
	if (!ir) {
		retval = -ENODEV;
		goto error;
	}

	dev_dbg(ir->d.dev, LOGHEAD "open called\n", ir->d.name, ir->d.minor);

	if (ir->d.minor == NOPLUG) {
		retval = -ENODEV;
		goto error;
	}

	if (ir->open) {
		retval = -EBUSY;
		goto error;
	}

	if (ir->d.rdev) {
		retval = rc_open(ir->d.rdev);
		if (retval)
			goto error;
	}

	cdev = ir->cdev;
	if (try_module_get(cdev->owner)) {
		ir->open++;
		retval = ir->d.set_use_inc(ir->d.data);

		if (retval) {
			module_put(cdev->owner);
			ir->open--;
		} else {
			lirc_buffer_clear(ir->buf);
		}
		if (ir->task)
			wake_up_process(ir->task);
	}

error:
	if (ir)
		dev_dbg(ir->d.dev, LOGHEAD "open result = %d\n",
			ir->d.name, ir->d.minor, retval);

	mutex_unlock(&lirc_dev_lock);

	nonseekable_open(inode, file);

	return retval;
}
