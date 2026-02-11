parport_daisy_fini(struct parport *port)
{
	struct daisydev **p;

	spin_lock(&topology_lock);
	p = &topology;
	while (*p) {
		struct daisydev *dev = *p;
		if (dev->port != port) {
			p = &dev->next;
			continue;
		}
		*p = dev->next;
		kfree(dev);
	}


	if (!topology) numdevs = 0;
	spin_unlock(&topology_lock);
	return;
}
