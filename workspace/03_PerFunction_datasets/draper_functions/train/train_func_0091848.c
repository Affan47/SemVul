tmdc_connect(struct gameport *gameport, struct gameport_driver *drv)
{
	unsigned char data[2][TMDC_MAX_LENGTH];
	struct tmdc *tmdc;
	int i;
	int err;

	if (!(tmdc = kzalloc(sizeof(struct tmdc), GFP_KERNEL)))
		return -ENOMEM;

	tmdc->gameport = gameport;

	gameport_set_drvdata(gameport, tmdc);

	err = gameport_open(gameport, drv, GAMEPORT_MODE_RAW);
	if (err)
		goto fail1;

	if (!(tmdc->exists = tmdc_read_packet(gameport, data))) {
		err = -ENODEV;
		goto fail2;
	}

	gameport_set_poll_handler(gameport, tmdc_poll);
	gameport_set_poll_interval(gameport, 20);

	for (i = 0; i < 2; i++) {
		if (tmdc->exists & (1 << i)) {

			err = tmdc_setup_port(tmdc, i, data[i]);
			if (err)
				goto fail3;
		}
	}

	return 0;

 fail3: while (--i >= 0) {
		if (tmdc->port[i]) {
			input_unregister_device(tmdc->port[i]->dev);
			kfree(tmdc->port[i]);
		}
	}
 fail2:	gameport_close(gameport);
 fail1:	gameport_set_drvdata(gameport, NULL);
	kfree(tmdc);
	return err;
}
