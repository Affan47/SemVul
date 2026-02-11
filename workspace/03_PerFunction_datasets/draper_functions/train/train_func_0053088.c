cx8802_alloc_frontends(struct cx8802_dev *dev)
{
	struct cx88_core *core = dev->core;
	struct vb2_dvb_frontend *fe = NULL;
	int i;

	mutex_init(&dev->frontends.lock);
	INIT_LIST_HEAD(&dev->frontends.felist);

	if (!core->board.num_frontends)
		return -ENODEV;

	printk(KERN_INFO "%s() allocating %d frontend(s)\n", __func__,
			 core->board.num_frontends);
	for (i = 1; i <= core->board.num_frontends; i++) {
		fe = vb2_dvb_alloc_frontend(&dev->frontends, i);
		if (!fe) {
			printk(KERN_ERR "%s() failed to alloc\n", __func__);
			vb2_dvb_dealloc_frontends(&dev->frontends);
			return -ENOMEM;
		}
	}
	return 0;
}
