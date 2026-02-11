acceptor_thread(void *arg)
{
    struct client_data *cdata;
    usbmuxd_scan_result *dev_list = NULL;
    pthread_t ctos;
    int count;

    if (!arg) {
	fprintf(stderr, "invalid client_data provided!\n");
	return NULL;
    }

    cdata = (struct client_data*)arg;

    if ((count = usbmuxd_scan(&dev_list)) < 0) {
	printf("Connecting to usbmuxd failed, terminating.\n");
	free(dev_list);
	return NULL;
    }

    fprintf(stdout, "Number of available devices == %d\n", count);

    if (dev_list == NULL || dev_list[0].handle == 0) {
	printf("No connected device found, terminating.\n");
	free(dev_list);
	return NULL;
    }

    fprintf(stdout, "Requesting connecion to device handle == %d (serial: %s), port %d\n", dev_list[0].handle, dev_list[0].serial_number, device_port);

    cdata->sfd = usbmuxd_connect(dev_list[0].handle, device_port);
    free(dev_list);
    if (cdata->sfd < 0) {
    	fprintf(stderr, "Error connecting to device!\n");
    } else {
	cdata->stop_ctos = 0;
	pthread_create(&ctos, NULL, run_ctos_loop, cdata);
	pthread_join(ctos, NULL);
    }

    if (cdata->fd > 0) {
	close(cdata->fd);
    }
    if (cdata->sfd > 0) {
	close(cdata->sfd);
    }

    return NULL;
}
