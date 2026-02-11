gameport_open(struct gameport *gameport, struct gameport_driver *drv, int mode)
{
	if (gameport->open) {
		if (gameport->open(gameport, mode)) {
			return -1;
		}
	} else {
		if (mode != GAMEPORT_MODE_RAW)
			return -1;
	}

	gameport_set_drv(gameport, drv);
	return 0;
}
