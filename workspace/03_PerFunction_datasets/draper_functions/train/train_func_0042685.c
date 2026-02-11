exit_process(CPROCESS *_object)
{
	#ifdef DEBUG_ME
	fprintf(stderr, "exit_process: %p\n", _object);
	#endif

	if (THIS->in >= 0)
	{
		if (THIS->in != THIS->out)
			close(THIS->in);
		THIS->in = -1;
	}

	if (THIS->out >= 0)
	{
		GB_Watch(THIS->out, GB_WATCH_NONE, NULL, 0);
		close(THIS->out);
		THIS->out = -1;
	}

	if (THIS->err >= 0)
	{
		GB_Watch(THIS->err, GB_WATCH_NONE, NULL, 0);
		close(THIS->err);
		THIS->err = -1;
	}


	STREAM_close(&THIS->ob.stream);
}
