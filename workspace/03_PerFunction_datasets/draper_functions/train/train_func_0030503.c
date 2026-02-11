av7110_wait_msgstate(struct av7110 *av7110, u16 flags)
{
	unsigned long start;
	u32 stat;
	int err;

	if (FW_VERSION(av7110->arm_app) <= 0x261c) {

		msleep(50);
		return 0;
	}


	start = jiffies;
	for (;;) {
		err = time_after(jiffies, start + ARM_WAIT_FREE);
		if (mutex_lock_interruptible(&av7110->dcomlock))
			return -ERESTARTSYS;
		stat = rdebi(av7110, DEBINOSWAP, MSGSTATE, 0, 2);
		mutex_unlock(&av7110->dcomlock);
		if ((stat & flags) == 0)
			break;
		if (err) {
			printk(KERN_ERR "%s: timeout waiting for MSGSTATE %04x\n",
				__func__, stat & flags);
			return -ETIMEDOUT;
		}
		msleep(1);
	}
	return 0;
}
