hvc_remove(struct hvc_struct *hp)
{
	unsigned long flags;
	struct tty_struct *tty;

	tty = tty_port_tty_get(&hp->port);

	spin_lock_irqsave(&hp->lock, flags);
	if (hp->index < MAX_NR_HVC_CONSOLES) {
		console_lock();
		vtermnos[hp->index] = -1;
		cons_ops[hp->index] = NULL;
		console_unlock();
	}


	spin_unlock_irqrestore(&hp->lock, flags);


	tty_port_put(&hp->port);


	if (tty) {
		tty_vhangup(tty);
		tty_kref_put(tty);
	}
	return 0;
}
