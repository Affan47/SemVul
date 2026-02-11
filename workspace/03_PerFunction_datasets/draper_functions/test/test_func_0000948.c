parport_ieee1284_epp_read_data (struct parport *port,
				       void *buffer, size_t len,
				       int flags)
{
	unsigned char *bp = (unsigned char *) buffer;
	unsigned ret = 0;


	parport_frob_control (port,
			      PARPORT_CONTROL_STROBE |
			      PARPORT_CONTROL_AUTOFD |
			      PARPORT_CONTROL_SELECT |
			      PARPORT_CONTROL_INIT,
			      PARPORT_CONTROL_INIT);
	port->ops->data_reverse (port);
	for (; len > 0; len--, bp++) {

		parport_frob_control (port,
				      PARPORT_CONTROL_AUTOFD,
				      PARPORT_CONTROL_AUTOFD);

		if (parport_wait_peripheral (port, PARPORT_STATUS_BUSY, 0)) {
			break;
		}

		*bp = parport_read_data (port);


		parport_frob_control (port, PARPORT_CONTROL_AUTOFD, 0);


		if (parport_poll_peripheral (port, PARPORT_STATUS_BUSY,
					     PARPORT_STATUS_BUSY, 5)) {
			break;
		}

		ret++;
	}
	port->ops->data_forward (port);

	return ret;
}
