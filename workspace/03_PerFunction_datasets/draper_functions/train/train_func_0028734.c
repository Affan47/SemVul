__connman_service_clear_error(struct connman_service *service)
{
	DBG("service %p", service);

	if (service == NULL)
		return -EINVAL;

	if (service->state != CONNMAN_SERVICE_STATE_FAILURE)
		return -EINVAL;

	service->state_ipv4 = service->state_ipv6 =
						CONNMAN_SERVICE_STATE_UNKNOWN;
	set_error(service, CONNMAN_SERVICE_ERROR_UNKNOWN);

	if (service->favorite == TRUE)
		set_reconnect_state(service, TRUE);

	__connman_service_ipconfig_indicate_state(service,
					CONNMAN_SERVICE_STATE_IDLE,
					CONNMAN_IPCONFIG_TYPE_IPV6);


	if (service->state_ipv4 != CONNMAN_SERVICE_STATE_UNKNOWN &&
			service->state_ipv4 != CONNMAN_SERVICE_STATE_FAILURE)
		return 0;

	return __connman_service_ipconfig_indicate_state(service,
						CONNMAN_SERVICE_STATE_IDLE,
						CONNMAN_IPCONFIG_TYPE_IPV4);
}
