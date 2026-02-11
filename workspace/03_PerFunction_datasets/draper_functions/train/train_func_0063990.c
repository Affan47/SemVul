dump_streams()
{
	int i;
	char ra[50];
	streams *sid;
	if (!opts.log)
		return;
	LOG("Dumping streams:");
	for (i = 0; i < MAX_STREAMS; i++)
		if ((sid = get_sid_for(i)))
			LOG("%d|  a:%d rsock:%d type:%d play:%d remote:%s:%d", i,
					sid->adapter, sid->rsock, sid->type, sid->do_play,
					get_stream_rhost(i, ra, sizeof(ra)),
					ntohs (sid->sa.sin_port));
}
