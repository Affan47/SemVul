bsfilter_filtering_thread(void *data)
{
	while (!filter_th_done) {
		pthread_mutex_lock(&list_mutex);
		if (to_filter_data == NULL || to_filter_data->done == TRUE) {
			pthread_mutex_unlock(&list_mutex);
			debug_print("thread is waiting for something to filter\n");
			pthread_mutex_lock(&wait_mutex);
			pthread_cond_wait(&wait_cond, &wait_mutex);
			pthread_mutex_unlock(&wait_mutex);
		} else {
			debug_print("thread awaken with something to filter\n");
			to_filter_data->done = FALSE;
			bsfilter_do_filter(to_filter_data);
			pthread_mutex_unlock(&list_mutex);
			to_filter_data->done = TRUE;
			g_usleep(100);
		}
	}
	return NULL;
}
