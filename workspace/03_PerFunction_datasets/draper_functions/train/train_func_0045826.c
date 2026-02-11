event_declare (espeak_EVENT* event)
{
ENTER("event_declare");

	event_display(event);

	if (!event)
	{
		return EE_INTERNAL_ERROR;
	}

	int a_status = pthread_mutex_lock(&my_mutex);
	espeak_ERROR a_error = EE_OK;

	if (!a_status)
	{
		SHOW_TIME("event_declare > locked\n");
		espeak_EVENT* a_event = event_copy(event);
		a_error = push(a_event);
		if (a_error != EE_OK)
		{
			event_delete(a_event);
		}
		SHOW_TIME("event_declare > unlocking\n");
		a_status = pthread_mutex_unlock(&my_mutex);
	}


	SHOW_TIME("event_declare > post my_sem_start_is_required\n");
	sem_post(&my_sem_start_is_required);


	if (a_status != 0)
	{
		a_error = EE_INTERNAL_ERROR;
	}

	return a_error;
}
