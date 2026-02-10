main(int cnt, char *vec[])
{
	int iface;

	if (cnt < 2) {
		err("Usage:\n"
			"%s <UART device>\n"
			"UART device --> UART device node Ex: /dev/ttyS0\n",
			vec[0]);
		return EXIT_FAILURE;
	}

	signal(SIGTERM, app_sig_handler);
	signal(SIGINT, app_sig_handler);

	if ((iface = uart_init(vec[1])) < 0) {
		return EXIT_FAILURE;
	}

	if (pthread_create(&t_app, NULL, app_thread, (void *)iface)) {
		err("Unable to create application thread\n");
		return EXIT_FAILURE;
	}

	if (pthread_create(&t_rx, NULL, rx_thread, (void *)iface)) {
		err("Unable to create RX thread [%s]\n", strerror(errno));
		return EXIT_FAILURE;
	}
	pthread_join(t_rx, NULL);
	pthread_join(t_app, NULL);

	unlink(IN_PIPE_NAME);
	dbg ("APP: Exiting...\n");
	return EXIT_SUCCESS;
}
