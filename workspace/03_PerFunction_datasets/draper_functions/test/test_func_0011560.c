__repmgr_new_connection(env, connp, s, state)
	ENV *env;
	REPMGR_CONNECTION **connp;
	socket_t s;
	int state;
{
	REPMGR_CONNECTION *c;
	int ret;

	if ((ret = __os_calloc(env, 1, sizeof(REPMGR_CONNECTION), &c)) != 0)
		return (ret);
	if ((ret = __repmgr_alloc_cond(&c->drained)) != 0) {
		__os_free(env, c);
		return (ret);
	}
	if ((ret = __repmgr_init_waiters(env, &c->response_waiters)) != 0) {
		(void)__repmgr_free_cond(&c->drained);
		__os_free(env, c);
		return (ret);
	}

	c->fd = s;
	c->state = state;
	c->type = UNKNOWN_CONN_TYPE;
#ifdef DB_WIN32
	c->event_object = WSA_INVALID_EVENT;
#endif

	STAILQ_INIT(&c->outbound_queue);
	c->out_queue_length = 0;

	__repmgr_reset_for_reading(c);
	*connp = c;

	return (0);
}
