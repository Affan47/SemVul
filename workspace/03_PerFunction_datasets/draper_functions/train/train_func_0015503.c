__connman_service_set_provider_pending(struct connman_service *service,
							DBusMessage *msg)
{
	if (service->provider_pending != NULL) {
		DBG("service %p provider pending msg %p already exists",
			service, service->provider_pending);
		return;
	}

	service->provider_pending = msg;
	return;
}
