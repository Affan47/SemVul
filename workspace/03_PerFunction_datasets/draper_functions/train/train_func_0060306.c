agp_find_controller_for_client(pid_t id)
{
	struct agp_controller *controller;

	controller = agp_fe.controllers;

	while (controller != NULL) {
		if ((agp_find_client_in_controller(controller, id)) != NULL)
			return controller;
		controller = controller->next;
	}

	return NULL;
}
