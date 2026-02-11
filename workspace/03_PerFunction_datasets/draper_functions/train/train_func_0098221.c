lirc_write(struct file *file, const char __user *buf,
			 size_t n, loff_t *ppos)
{
	int i, count;
	unsigned long flags;
	long delta = 0;
	int *wbuf;

	if (!(hardware[type].features & LIRC_CAN_SEND_PULSE))
		return -EPERM;

	count = n / sizeof(int);
	if (n % sizeof(int) || count % 2 == 0)
		return -EINVAL;
	wbuf = memdup_user(buf, n);
	if (IS_ERR(wbuf))
		return PTR_ERR(wbuf);
	spin_lock_irqsave(&hardware[type].lock, flags);
	if (type == LIRC_IRDEO) {

		on();
	}
	for (i = 0; i < count; i++) {
		if (i%2)
			hardware[type].send_space(wbuf[i] - delta);
		else
			delta = hardware[type].send_pulse(wbuf[i]);
	}
	off();
	spin_unlock_irqrestore(&hardware[type].lock, flags);
	kfree(wbuf);
	return n;
}
