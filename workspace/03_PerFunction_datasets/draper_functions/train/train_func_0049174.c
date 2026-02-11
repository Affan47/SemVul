analog_init_port(struct gameport *gameport, struct gameport_driver *drv, struct analog_port *port)
{
	int i, t, u, v;

	port->gameport = gameport;

	gameport_set_drvdata(gameport, port);

	if (!gameport_open(gameport, drv, GAMEPORT_MODE_RAW)) {

		analog_calibrate_timer(port);

		gameport_trigger(gameport);
		t = gameport_read(gameport);
		msleep(ANALOG_MAX_TIME);
		port->mask = (gameport_read(gameport) ^ t) & t & 0xf;
		port->fuzz = (port->speed * ANALOG_FUZZ_MAGIC) / port->loop / 1000 + ANALOG_FUZZ_BITS;

		for (i = 0; i < ANALOG_INIT_RETRIES; i++) {
			if (!analog_cooked_read(port))
				break;
			msleep(ANALOG_MAX_TIME);
		}

		u = v = 0;

		msleep(ANALOG_MAX_TIME);
		t = gameport_time(gameport, ANALOG_MAX_TIME * 1000);
		gameport_trigger(gameport);
		while ((gameport_read(port->gameport) & port->mask) && (u < t))
			u++;
		udelay(ANALOG_SAITEK_DELAY);
		t = gameport_time(gameport, ANALOG_SAITEK_TIME);
		gameport_trigger(gameport);
		while ((gameport_read(port->gameport) & port->mask) && (v < t))
			v++;

		if (v < (u >> 1)) {
			analog_options[0] |=
				ANALOG_SAITEK | ANALOG_BTNS_CHF | ANALOG_HBTN_CHF | ANALOG_HAT1_CHF;
			return 0;
		}

		gameport_close(gameport);
	}

	if (!gameport_open(gameport, drv, GAMEPORT_MODE_COOKED)) {

		for (i = 0; i < ANALOG_INIT_RETRIES; i++)
			if (!gameport_cooked_read(gameport, port->axes, &port->buttons))
				break;
		for (i = 0; i < 4; i++)
			if (port->axes[i] != -1)
				port->mask |= 1 << i;

		port->fuzz = gameport->fuzz;
		port->cooked = 1;
		return 0;
	}

	return gameport_open(gameport, drv, GAMEPORT_MODE_RAW);
}
