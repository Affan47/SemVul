parport_pc_compat_write_block_pio(struct parport *port,
						 const void *buf, size_t length,
						 int flags)
{
	size_t written;
	int r;
	unsigned long expire;
	const struct parport_pc_private *priv = port->physport->private_data;


	if (port->physport->cad->timeout <= PARPORT_INACTIVITY_O_NONBLOCK)
		return parport_ieee1284_write_compat(port, buf,
						      length, flags);


	parport_pc_data_forward(port);
	parport_pc_frob_control(port, PARPORT_CONTROL_STROBE, 0);
	r = change_mode(port, ECR_PPF);
	if (r)
		printk(KERN_DEBUG "%s: Warning change_mode ECR_PPF failed\n",
								port->name);

	port->physport->ieee1284.phase = IEEE1284_PH_FWD_DATA;


	written = parport_pc_fifo_write_block(port, buf, length);


	expire = jiffies + (priv->fifo_depth * HZ * 4);
	do {

		r = change_mode(port, ECR_PS2);
		if (r != -EBUSY)
			break;
	} while (time_before(jiffies, expire));
	if (r == -EBUSY) {

		printk(KERN_DEBUG "%s: FIFO is stuck\n", port->name);


		frob_set_mode(port, ECR_TST);


		for (written -= priv->fifo_depth; ; written++) {
			if (inb(ECONTROL(port)) & 0x2) {

				break;
			}
			outb(0, FIFO(port));
		}


		frob_set_mode(port, ECR_PS2);
	}

	r = parport_wait_peripheral(port,
				     PARPORT_STATUS_BUSY,
				     PARPORT_STATUS_BUSY);
	if (r)
		printk(KERN_DEBUG
			"%s: BUSY timeout (%d) in compat_write_block_pio\n",
			port->name, r);

	port->physport->ieee1284.phase = IEEE1284_PH_FWD_IDLE;

	return written;
}
