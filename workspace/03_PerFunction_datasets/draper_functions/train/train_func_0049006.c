__connman_service_session_dec(struct connman_service *service)
{
	DBG("service %p ref count %d", service,
		service->session_usage_count - 1);

	if (__sync_fetch_and_sub(&service->session_usage_count, 1) != 1)
		return FALSE;

	return TRUE;
}
