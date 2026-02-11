tty_exit(struct nozomi *dc)
{
	unsigned int i;

	DBG1(" ");

	for (i = 0; i < MAX_PORT; ++i)
		tty_port_tty_hangup(&dc->port[i].port, false);


	while (dc->open_ttys)
		msleep(1);
	for (i = 0; i < MAX_PORT; ++i) {
		tty_unregister_device(ntty_driver, dc->index_start + i);
		tty_port_destroy(&dc->port[i].port);
	}
}
