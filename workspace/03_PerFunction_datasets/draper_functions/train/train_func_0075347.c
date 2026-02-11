gameport_close(struct gameport *gameport)
{
	del_timer_sync(&gameport->poll_timer);
	gameport->poll_handler = NULL;
	gameport->poll_interval = 0;
	gameport_set_drv(gameport, NULL);
	if (gameport->close)
		gameport->close(gameport);
}
