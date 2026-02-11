fwserial_close_port(struct tty_driver *driver,
				struct fwtty_port *port)
{
	struct tty_struct *tty;

	mutex_lock(&port->port.mutex);
	tty = tty_port_tty_get(&port->port);
	if (tty) {
		tty_vhangup(tty);
		tty_kref_put(tty);
	}
	mutex_unlock(&port->port.mutex);

	if (driver == fwloop_driver)
		tty_unregister_device(driver, loop_idx(port));
	else
		tty_unregister_device(driver, port->index);
}
