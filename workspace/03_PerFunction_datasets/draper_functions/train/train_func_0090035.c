saa7134_tvaudio_init2(struct saa7134_dev *dev)
{
	int (*my_thread)(void *data) = NULL;

	switch (dev->pci->device) {
	case PCI_DEVICE_ID_PHILIPS_SAA7134:
		my_thread = tvaudio_thread;
		break;
	case PCI_DEVICE_ID_PHILIPS_SAA7133:
	case PCI_DEVICE_ID_PHILIPS_SAA7135:
		my_thread = tvaudio_thread_ddep;
		break;
	}

	dev->thread.thread = NULL;
	dev->thread.scan1 = dev->thread.scan2 = 0;
	if (my_thread) {
		saa7134_tvaudio_init(dev);

		dev->thread.thread = kthread_run(my_thread, dev, "%s", dev->name);
		if (IS_ERR(dev->thread.thread)) {
			pr_warn("%s: kernel_thread() failed\n",
			       dev->name);

		}
	}

	saa7134_enable_i2s(dev);
	return 0;
}
