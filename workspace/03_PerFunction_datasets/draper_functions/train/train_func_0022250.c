launch_service(struct outgoing *o)
{
	pthread_t t;
	int ret;

	if ((ret = ast_pthread_create_detached(&t, NULL, attempt_thread, o))) {
		ast_log(LOG_WARNING, "Unable to create thread :( (returned error: %d)\n", ret);
		free_outgoing(o);
	}
}
