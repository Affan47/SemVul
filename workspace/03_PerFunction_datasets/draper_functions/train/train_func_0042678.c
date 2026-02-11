a3d_disconnect(struct gameport *gameport)
{
	struct a3d *a3d = gameport_get_drvdata(gameport);

	input_unregister_device(a3d->dev);
	if (a3d->adc)
		gameport_unregister_port(a3d->adc);
	gameport_close(gameport);
	gameport_set_drvdata(gameport, NULL);
	kfree(a3d);
}
