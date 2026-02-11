find_service_action(struct service_action *service_action, uint32_t action)
{
	while (service_action->cmd_perform) {
		if (service_action->service_action == action)
			return service_action;
		service_action++;
	}
	return NULL;
}
