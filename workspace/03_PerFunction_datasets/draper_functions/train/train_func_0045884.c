x25_asy_encaps(struct x25_asy *sl, unsigned char *icp, int len)
{
	unsigned char *p;
	int actual, count, mtu = sl->dev->mtu;

	if (len > mtu) {

		len = mtu;
		printk(KERN_DEBUG "%s: truncating oversized transmit packet!\n",
					sl->dev->name);
		sl->dev->stats.tx_dropped++;
		x25_asy_unlock(sl);
		return;
	}

	p = icp;
	count = x25_asy_esc(p, sl->xbuff, len);


	set_bit(TTY_DO_WRITE_WAKEUP, &sl->tty->flags);
	actual = sl->tty->ops->write(sl->tty, sl->xbuff, count);
	sl->xleft = count - actual;
	sl->xhead = sl->xbuff + actual;

	clear_bit(SLF_OUTWAIT, &sl->flags);
}
