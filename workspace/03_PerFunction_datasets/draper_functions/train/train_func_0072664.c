tty_port_open(struct tty_port *port, struct tty_struct *tty,
							struct file *filp)
{
	spin_lock_irq(&port->lock);
	++port->count;
	spin_unlock_irq(&port->lock);
	tty_port_tty_set(port, tty);


	mutex_lock(&port->mutex);

	if (!test_bit(ASYNCB_INITIALIZED, &port->flags)) {
		clear_bit(TTY_IO_ERROR, &tty->flags);
		if (port->ops->activate) {
			int retval = port->ops->activate(port, tty);
			if (retval) {
				mutex_unlock(&port->mutex);
				return retval;
			}
		}
		set_bit(ASYNCB_INITIALIZED, &port->flags);
	}
	mutex_unlock(&port->mutex);
	return tty_port_block_til_ready(port, tty, filp);
}
