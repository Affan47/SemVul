gameport_destroy_port(struct gameport *gameport)
{
	struct gameport *child;

	child = gameport_get_pending_child(gameport);
	if (child) {
		gameport_remove_pending_events(child);
		put_device(&child->dev);
	}

	if (gameport->parent) {
		gameport->parent->child = NULL;
		gameport->parent = NULL;
	}

	if (device_is_registered(&gameport->dev))
		device_del(&gameport->dev);

	list_del_init(&gameport->node);

	gameport_remove_pending_events(gameport);
	put_device(&gameport->dev);
}
