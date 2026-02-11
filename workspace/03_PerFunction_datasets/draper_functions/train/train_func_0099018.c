mISDN_register_clock(char *name, int pri, clockctl_func_t *ctl, void *priv)
{
	u_long			flags;
	struct mISDNclock	*iclock;

	if (*debug & (DEBUG_CORE | DEBUG_CLOCK))
		printk(KERN_DEBUG "%s: %s %d\n", __func__, name, pri);
	iclock = kzalloc(sizeof(struct mISDNclock), GFP_ATOMIC);
	if (!iclock) {
		printk(KERN_ERR "%s: No memory for clock entry.\n", __func__);
		return NULL;
	}
	strncpy(iclock->name, name, sizeof(iclock->name) - 1);
	iclock->pri = pri;
	iclock->priv = priv;
	iclock->ctl = ctl;
	write_lock_irqsave(&iclock_lock, flags);
	list_add_tail(&iclock->list, &iclock_list);
	select_iclock();
	write_unlock_irqrestore(&iclock_lock, flags);
	return iclock;
}
