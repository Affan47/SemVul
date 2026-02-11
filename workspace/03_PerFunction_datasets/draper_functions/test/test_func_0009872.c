ks0108_parport_attach(struct parport *port)
{
	struct pardev_cb ks0108_cb;

	if (port->base != ks0108_port)
		return;

	memset(&ks0108_cb, 0, sizeof(ks0108_cb));
	ks0108_cb.flags = PARPORT_DEV_EXCL;
	ks0108_pardevice = parport_register_dev_model(port, KS0108_NAME,
						      &ks0108_cb, 0);
	if (!ks0108_pardevice) {
		pr_err("ERROR: parport didn't register new device\n");
		return;
	}
	if (parport_claim(ks0108_pardevice)) {
		pr_err("could not claim access to parport %i. Aborting.\n",
		       ks0108_port);
		goto err_unreg_device;
	}

	ks0108_parport = port;
	ks0108_inited = 1;
	return;

err_unreg_device:
	parport_unregister_device(ks0108_pardevice);
	ks0108_pardevice = NULL;
}
