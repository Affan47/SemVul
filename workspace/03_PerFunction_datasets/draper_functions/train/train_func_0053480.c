sl_keepalive(unsigned long sls)
{
	struct slip *sl = (struct slip *)sls;

	spin_lock(&sl->lock);

	if (sl->tty == NULL)
		goto out;

	if (sl->keepalive) {
		if (test_bit(SLF_KEEPTEST, &sl->flags)) {

			if (sl->outfill)

				(void)del_timer(&sl->outfill_timer);
			printk(KERN_DEBUG "%s: no packets received during keepalive timeout, hangup.\n", sl->dev->name);

			tty_hangup(sl->tty);

			goto out;
		} else
			set_bit(SLF_KEEPTEST, &sl->flags);

		mod_timer(&sl->keepalive_timer, jiffies+sl->keepalive*HZ);
	}
out:
	spin_unlock(&sl->lock);
}
