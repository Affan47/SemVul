add_tty(int j,
		    struct ipw_hardware *hardware,
		    struct ipw_network *network, int channel_idx,
		    int secondary_channel_idx, int tty_type)
{
	ttys[j] = kzalloc(sizeof(struct ipw_tty), GFP_KERNEL);
	if (!ttys[j])
		return -ENOMEM;
	ttys[j]->index = j;
	ttys[j]->hardware = hardware;
	ttys[j]->channel_idx = channel_idx;
	ttys[j]->secondary_channel_idx = secondary_channel_idx;
	ttys[j]->network = network;
	ttys[j]->tty_type = tty_type;
	mutex_init(&ttys[j]->ipw_tty_mutex);
	tty_port_init(&ttys[j]->port);

	tty_port_register_device(&ttys[j]->port, ipw_tty_driver, j, NULL);
	ipwireless_associate_network_tty(network, channel_idx, ttys[j]);

	if (secondary_channel_idx != -1)
		ipwireless_associate_network_tty(network,
						 secondary_channel_idx,
						 ttys[j]);

	if (get_tty(j))
		printk(KERN_INFO IPWIRELESS_PCCARD_NAME
		       ": registering %s device ttyIPWp%d\n",
		       tty_type_name(tty_type), j);

	return 0;
}
