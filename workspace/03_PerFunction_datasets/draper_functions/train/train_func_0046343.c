cobra_disconnect(struct gameport *gameport)
{
	struct cobra *cobra = gameport_get_drvdata(gameport);
	int i;

	for (i = 0; i < 2; i++)
		if ((cobra->exists >> i) & 1)
			input_unregister_device(cobra->dev[i]);
	gameport_close(gameport);
	gameport_set_drvdata(gameport, NULL);
	kfree(cobra);
}
