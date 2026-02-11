connman_service_set_proxy_method(struct connman_service *service,
					enum connman_service_proxy_method method)
{
	if (service == NULL || service->hidden == TRUE)
		return;

	service->proxy = method;

	proxy_changed(service);

	if (method != CONNMAN_SERVICE_PROXY_METHOD_AUTO)
		__connman_notifier_proxy_changed(service);
}
