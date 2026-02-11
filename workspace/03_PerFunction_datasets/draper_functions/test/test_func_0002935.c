auto_connect_service(GSequenceIter* iter,
		connman_bool_t preferred)
{
	struct connman_service *service = NULL;

	while (g_sequence_iter_is_end(iter) == FALSE) {
		service = g_sequence_get(iter);

		if (service->pending != NULL)
			return TRUE;

		if (is_connecting(service) == TRUE)
			return TRUE;

		if (service->favorite == FALSE) {
			if (preferred == TRUE)
				goto next_service;
			return FALSE;
		}

		if (is_connected(service) == TRUE)
			return TRUE;

		if (is_ignore(service) == FALSE && service->state ==
				CONNMAN_SERVICE_STATE_IDLE)
			break;

	next_service:
		service = NULL;

		iter = g_sequence_iter_next(iter);
	}

	if (service != NULL) {

		DBG("service %p %s %s", service, service->name,
				(preferred == TRUE)? "preferred": "auto");

		service->userconnect = FALSE;
		__connman_service_connect(service);
		return TRUE;
	}
	return FALSE;
}
