agp_remove_client(pid_t id)
{
	struct agp_client *client;
	struct agp_client *prev_client;
	struct agp_client *next_client;
	struct agp_controller *controller;

	controller = agp_find_controller_for_client(id);
	if (controller == NULL)
		return -EINVAL;

	client = agp_find_client_in_controller(controller, id);
	if (client == NULL)
		return -EINVAL;

	prev_client = client->prev;
	next_client = client->next;

	if (prev_client != NULL) {
		prev_client->next = next_client;
		if (next_client != NULL)
			next_client->prev = prev_client;

	} else {
		if (next_client != NULL)
			next_client->prev = NULL;
		controller->clients = next_client;
	}

	controller->num_clients--;
	agp_remove_seg_from_client(client);
	kfree(client);
	return 0;
}
