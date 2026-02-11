read_dmx(sockets * s)
{
	static int cnt;
	streams *sid;
	adapter *ad;
	int send = 0, flush_all = 0, ls, lse;
	uint64_t stime;

	if (s->rlen % DVB_FRAME != 0)

		return 0;

	if (s->rlen == s->lbuf)
		cnt++;
	else
		cnt = 0;
	ad = get_adapter(s->sid);
	if (!ad)
	{
		s->rlen = 0;
		return 0;
	}

	if (s->rtime - ad->rtime > 50)
	{
		flush_all = 1;
		send = 1;
	}

	if (flush_all && (s->rlen > 20000))
		send = 0;

	if (s->rlen == s->lbuf)
		send = 1;

	if (s->rtime - ad->rtime > 1000)
		send = 1;

	LOGL(7,
			"read_dmx send=%d, flush_all=%d, cnt %d called for adapter %d -> %d out of %d bytes read, %jd ms ago",
			send, flush_all, cnt, s->sid, s->rlen, s->lbuf,
			s->rtime - ad->rtime);

	if (!send)
		return 0;

	ls = lock_streams_for_adapter(ad->id);
	adapter_lock(ad->id);
	process_dmx(s);
	adapter_unlock(ad->id);
	lse = unlock_streams_for_adapter(ad->id);
	if (ls != lse)
		LOG("leak detected %d %d!!! ", ls, lse);
	return 0;
}
