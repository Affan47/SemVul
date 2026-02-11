logs_free(LOGS *logs)
{
	LIST *l;

	os_lock_lock(logs->lock);

	for(l = logs->logs; l ; l = l->next)
	{
		log_free((LOG *)l->data);
	}
	logs->logs = list_free(logs->logs);
	logs->lock = os_lock_free(logs->lock);

	return (LOGS *)os_free(logs);
}
