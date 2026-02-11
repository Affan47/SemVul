parport_release(struct pardevice *dev)
{
	struct parport *port = dev->port->physport;
	struct pardevice *pd;
	unsigned long flags;


	write_lock_irqsave(&port->cad_lock, flags);
	if (port->cad != dev) {
		write_unlock_irqrestore (&port->cad_lock, flags);
		printk(KERN_WARNING "%s: %s tried to release parport "
		       "when not owner\n", port->name, dev->name);
		return;
	}

#ifdef CONFIG_PARPORT_1284

	if (dev->port->muxport >= 0) {

		port->muxsel = -1;
	}


	if (dev->daisy >= 0) {
		parport_daisy_deselect_all (port);
		port->daisy = -1;
	}
#endif

	port->cad = NULL;
	write_unlock_irqrestore(&port->cad_lock, flags);


	port->ops->save_state(port, dev->state);


	for (pd = port->waithead; pd; pd = pd->waitnext) {
		if (pd->waiting & 2) {
			parport_claim(pd);
			if (waitqueue_active(&pd->wait_q))
				wake_up_interruptible(&pd->wait_q);
			return;
		} else if (pd->wakeup) {
			pd->wakeup(pd->private);
			if (dev->port->cad)
				return;
		} else {
			printk(KERN_ERR "%s: don't know how to wake %s\n", port->name, pd->name);
		}
	}


	for (pd = port->devices; (port->cad == NULL) && pd; pd = pd->next) {
		if (pd->wakeup && pd != dev)
			pd->wakeup(pd->private);
	}
}
