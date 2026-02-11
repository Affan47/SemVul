streams_add()
{
	int i;
	streams *ss;
	i = add_new_lock((void **) st, MAX_STREAMS, sizeof(streams), &st_mutex);
	if (i == -1)
		LOG_AND_RETURN(-1, "streams_add failed");

	ss = st[i];
	ss->enabled = 1;
	ss->adapter = -1;
	ss->sid = i;
	ss->rsock = -1;
	ss->rsock_err = 0;
	ss->type = 0;
	ss->do_play = 0;
	ss->iiov = 0;
	ss->sp = ss->sb = 0;
	memset(&ss->iov, 0, sizeof(ss->iiov));
	init_dvb_parameters(&ss->tp);
	ss->useragent[0] = 0;
	ss->len = 0;
	ss->st_sock = -1;

	ss->ssrc = random();
	ss->timeout = opts.timeout_sec;
	ss->wtime = ss->rtcp_wtime = getTick();

	ss->total_len = 7 * DVB_FRAME;
	mutex_unlock(&ss->mutex);
	return i;
}
