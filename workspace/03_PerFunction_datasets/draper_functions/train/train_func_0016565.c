nutscan_scan_eaton_serial_shut(const char* port_name)
{
	nutscan_device_t * dev = NULL;
	int devfd = -1;

	if ( (devfd = ser_open_nf(port_name)) != -1 ) {


		if (ser_set_dtr(devfd, 0) != -1) {

			ser_set_rts(devfd, 1);
			ser_set_speed_nf(devfd, port_name, B2400);

			if (shut_synchronise(devfd)) {


				dev = nutscan_new_device();
				dev->type = TYPE_EATON_SERIAL;
				dev->driver = strdup(SHUT_DRIVER_NAME);
				dev->port = strdup(port_name);
#ifdef HAVE_PTHREAD
				pthread_mutex_lock(&dev_mutex);
#endif
				dev_ret = nutscan_add_device_to_device(dev_ret, dev);
#ifdef HAVE_PTHREAD
				pthread_mutex_unlock(&dev_mutex);
#endif
			}
		}

		ser_close(devfd, NULL);
	}

	return dev;
}
