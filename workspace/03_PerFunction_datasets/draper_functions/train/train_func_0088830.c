agp_find_client_by_pid(pid_t id)
{
	struct agp_client *temp;

	if (agp_fe.current_controller == NULL)
		return NULL;

	temp = agp_find_client_in_controller(agp_fe.current_controller, id);
	return temp;
}
