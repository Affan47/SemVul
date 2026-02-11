usblp_read(struct file *file, char __user *buffer, size_t len, loff_t *ppos)
{
	struct usblp *usblp = file->private_data;
	ssize_t count;
	ssize_t avail;
	int rv;

	if (!usblp->bidir)
		return -EINVAL;

	rv = usblp_rwait_and_lock(usblp, !!(file->f_flags & O_NONBLOCK));
	if (rv < 0)
		return rv;

	if ((avail = usblp->rstatus) < 0) {
		printk(KERN_ERR "usblp%d: error %d reading from printer\n",
		    usblp->minor, (int)avail);
		usblp_submit_read(usblp);
		count = -EIO;
		goto done;
	}

	count = len < avail - usblp->readcount ? len : avail - usblp->readcount;
	if (count != 0 &&
	    copy_to_user(buffer, usblp->readbuf + usblp->readcount, count)) {
		count = -EFAULT;
		goto done;
	}

	if ((usblp->readcount += count) == avail) {
		if (usblp_submit_read(usblp) < 0) {

			if (count == 0)
				count = -EIO;
			goto done;
		}
	}

done:
	mutex_unlock(&usblp->mut);
	return count;
}
