tty_port_link_device(struct tty_port *port,
		struct tty_driver *driver, unsigned index)
{
	if (WARN_ON(index >= driver->num))
		return;
	driver->ports[index] = port;
}
