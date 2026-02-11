dgap_tty_register_ports(struct board_t *brd)
{
	struct channel_t *ch;
	int i;
	int ret;

	brd->serial_ports = kcalloc(brd->nasync, sizeof(*brd->serial_ports),
					GFP_KERNEL);
	if (!brd->serial_ports)
		return -ENOMEM;

	brd->printer_ports = kcalloc(brd->nasync, sizeof(*brd->printer_ports),
					GFP_KERNEL);
	if (!brd->printer_ports) {
		ret = -ENOMEM;
		goto free_serial_ports;
	}

	for (i = 0; i < brd->nasync; i++) {
		tty_port_init(&brd->serial_ports[i]);
		tty_port_init(&brd->printer_ports[i]);
	}

	ch = brd->channels[0];
	for (i = 0; i < brd->nasync; i++, ch = brd->channels[i]) {
		struct device *classp;

		classp = tty_port_register_device(&brd->serial_ports[i],
						  brd->serial_driver,
						  i, NULL);

		if (IS_ERR(classp)) {
			ret = PTR_ERR(classp);
			goto unregister_ttys;
		}

		dgap_create_tty_sysfs(&ch->ch_tun, classp);
		ch->ch_tun.un_sysfs = classp;

		classp = tty_port_register_device(&brd->printer_ports[i],
						  brd->print_driver,
						  i, NULL);

		if (IS_ERR(classp)) {
			ret = PTR_ERR(classp);
			goto unregister_ttys;
		}

		dgap_create_tty_sysfs(&ch->ch_pun, classp);
		ch->ch_pun.un_sysfs = classp;
	}
	dgap_create_ports_sysfiles(brd);

	return 0;

unregister_ttys:
	while (i >= 0) {
		ch = brd->channels[i];
		if (ch->ch_tun.un_sysfs) {
			dgap_remove_tty_sysfs(ch->ch_tun.un_sysfs);
			tty_unregister_device(brd->serial_driver, i);
		}

		if (ch->ch_pun.un_sysfs) {
			dgap_remove_tty_sysfs(ch->ch_pun.un_sysfs);
			tty_unregister_device(brd->print_driver, i);
		}
		i--;
	}

	for (i = 0; i < brd->nasync; i++) {
		tty_port_destroy(&brd->serial_ports[i]);
		tty_port_destroy(&brd->printer_ports[i]);
	}

	kfree(brd->printer_ports);
	brd->printer_ports = NULL;

free_serial_ports:
	kfree(brd->serial_ports);
	brd->serial_ports = NULL;

	return ret;
}
