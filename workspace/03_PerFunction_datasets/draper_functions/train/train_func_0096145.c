free_port(struct device *dev)
{
	int d;
	struct parport *port = to_parport_dev(dev);

	spin_lock(&full_list_lock);
	list_del(&port->full_list);
	spin_unlock(&full_list_lock);
	for (d = 0; d < 5; d++) {
		kfree(port->probe_info[d].class_name);
		kfree(port->probe_info[d].mfr);
		kfree(port->probe_info[d].model);
		kfree(port->probe_info[d].cmdset);
		kfree(port->probe_info[d].description);
	}

	kfree(port->name);
	kfree(port);
}
