pcmcia_bus_add_socket(struct device *dev,
					   struct class_interface *class_intf)
{
	struct pcmcia_socket *socket = dev_get_drvdata(dev);
	int ret;

	socket = pcmcia_get_socket(socket);
	if (!socket) {
		dev_err(dev, "PCMCIA obtaining reference to socket failed\n");
		return -ENODEV;
	}

	ret = sysfs_create_bin_file(&dev->kobj, &pccard_cis_attr);
	if (ret) {
		dev_err(dev, "PCMCIA registration failed\n");
		pcmcia_put_socket(socket);
		return ret;
	}

	INIT_LIST_HEAD(&socket->devices_list);
	socket->pcmcia_pfc = 0;
	socket->device_count = 0;
	atomic_set(&socket->present, 0);

	ret = pccard_register_pcmcia(socket, &pcmcia_bus_callback);
	if (ret) {
		dev_err(dev, "PCMCIA registration failed\n");
		pcmcia_put_socket(socket);
		return ret;
	}

	return 0;
}
