cavan_dynamic_service_join(struct cavan_dynamic_service *service)
{
	pthread_mutex_lock(&service->lock);

	while (service->count)
	{
		pd_bold_info("service %s daemon count %d", service->name, service->count);
		pthread_cond_wait(&service->cond, &service->lock);
	}

	if (service->state == CAVAN_SERVICE_STATE_RUNNING)
	{
		service->stop(service);
	}

	service->state = CAVAN_SERVICE_STATE_STOPPED;

	pthread_mutex_unlock(&service->lock);

	pd_bold_info("service %s stopped", service->name);
}
