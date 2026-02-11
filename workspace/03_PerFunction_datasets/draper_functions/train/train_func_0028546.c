parport_ieee1284_ecp_write_addr (struct parport *port,
					const void *buffer, size_t len,
					int flags)
{
#ifndef CONFIG_PARPORT_1284
	return 0;
#else
	const unsigned char *buf = buffer;
	size_t written;
	int retry;

	port = port->physport;

	if (port->ieee1284.phase != IEEE1284_PH_FWD_IDLE)
		if (ecp_reverse_to_forward (port))
			return 0;

	port->ieee1284.phase = IEEE1284_PH_FWD_DATA;


	parport_frob_control (port,
			      PARPORT_CONTROL_AUTOFD
			      | PARPORT_CONTROL_STROBE
			      | PARPORT_CONTROL_INIT,
			      PARPORT_CONTROL_AUTOFD
			      | PARPORT_CONTROL_INIT);
	for (written = 0; written < len; written++, buf++) {
		unsigned long expire = jiffies + port->cad->timeout;
		unsigned char byte;

		byte = *buf;
	try_again:
		parport_write_data (port, byte);
		parport_frob_control (port, PARPORT_CONTROL_STROBE,
				      PARPORT_CONTROL_STROBE);
		udelay (5);
		for (retry = 0; retry < 100; retry++) {
			if (!parport_wait_peripheral (port,
						      PARPORT_STATUS_BUSY, 0))
				goto success;

			if (signal_pending (current)) {
				parport_frob_control (port,
						      PARPORT_CONTROL_STROBE,
						      0);
				break;
			}
		}


		DPRINTK (KERN_DEBUG "%s: ECP transfer stalled!\n", port->name);

		parport_frob_control (port, PARPORT_CONTROL_INIT,
				      PARPORT_CONTROL_INIT);
		udelay (50);
		if (parport_read_status (port) & PARPORT_STATUS_PAPEROUT) {

			parport_frob_control (port, PARPORT_CONTROL_INIT, 0);
			break;
		}

		parport_frob_control (port, PARPORT_CONTROL_INIT, 0);
		udelay (50);
		if (!(parport_read_status (port) & PARPORT_STATUS_PAPEROUT))
			break;

		DPRINTK (KERN_DEBUG "%s: Host transfer recovered\n",
			 port->name);

		if (time_after_eq (jiffies, expire)) break;
		goto try_again;
	success:
		parport_frob_control (port, PARPORT_CONTROL_STROBE, 0);
		udelay (5);
		if (parport_wait_peripheral (port,
					     PARPORT_STATUS_BUSY,
					     PARPORT_STATUS_BUSY))

			break;
	}

	port->ieee1284.phase = IEEE1284_PH_FWD_IDLE;

	return written;
#endif
}
