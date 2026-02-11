output_init_pipe(struct output_s *o) {
	struct stat		st;

	if (!lstat(o->pipe.filename, &st)) {
		if (!S_ISFIFO(st.st_mode)) {
			logwrite(LOG_ERROR, "stream_pipe: %s exists and is not a pipe", o->pipe.filename);
			return 0;
		}
	} else {


		if (mknod(o->pipe.filename, S_IFIFO|0700, 0)) {
			logwrite(LOG_ERROR, "stream_pipe: failed to create fifo %s", o->pipe.filename);
			return 0;
		}
	}

	o->buffer=sb_init(PIPE_MAX_TS, TS_PACKET_SIZE, 0);

	if (!o->buffer)
		return 0;

	signal(SIGPIPE, SIG_IGN);

	output_pipe_event_init(o);

	return 1;
}
