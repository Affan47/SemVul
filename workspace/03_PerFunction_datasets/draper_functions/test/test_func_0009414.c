cavan_dynamic_service_stop(struct cavan_dynamic_service *service)
{
	pthread_mutex_lock(&service->lock);

	if (service->state == CAVAN_SERVICE_STATE_RUNNING)
	{
		int i;

		service->state = CAVAN_SERVICE_STATE_STOPPING;
		service->stop(service);

		for (i = 0; i < 10 && service->count; i++)
		{
			struct timespec abstime;

			cavan_timer_set_timespec(&abstime, 2000);
			pthread_cond_timedwait(&service->cond, &service->lock, &abstime);

			if (service->state == CAVAN_SERVICE_STATE_STOPPED)
			{
				break;
			}

			pd_red_info("wait service stop %d", i);
		}
	}

	pthread_mutex_unlock(&service->lock);

	return 0;
}
