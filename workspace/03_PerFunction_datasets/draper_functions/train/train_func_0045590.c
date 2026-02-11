mISDN_read(struct file *filep, char __user *buf, size_t count, loff_t *off)
{
	struct mISDNtimerdev	*dev = filep->private_data;
	struct list_head *list = &dev->expired;
	struct mISDNtimer	*timer;
	int	ret = 0;

	if (*debug & DEBUG_TIMER)
		printk(KERN_DEBUG "%s(%p, %p, %d, %p)\n", __func__,
		       filep, buf, (int)count, off);

	if (count < sizeof(int))
		return -ENOSPC;

	spin_lock_irq(&dev->lock);
	while (list_empty(list) && (dev->work == 0)) {
		spin_unlock_irq(&dev->lock);
		if (filep->f_flags & O_NONBLOCK)
			return -EAGAIN;
		wait_event_interruptible(dev->wait, (dev->work ||
						     !list_empty(list)));
		if (signal_pending(current))
			return -ERESTARTSYS;
		spin_lock_irq(&dev->lock);
	}
	if (dev->work)
		dev->work = 0;
	if (!list_empty(list)) {
		timer = list_first_entry(list, struct mISDNtimer, list);
		list_del(&timer->list);
		spin_unlock_irq(&dev->lock);
		if (put_user(timer->id, (int __user *)buf))
			ret = -EFAULT;
		else
			ret = sizeof(int);
		kfree(timer);
	} else {
		spin_unlock_irq(&dev->lock);
	}
	return ret;
}
