stream_create(char *name, audio_io_t *in, audio_codec_t *co, audio_io_t *out) {
	stream_t *s;

	debug("stream_create() name: %s in: 0x%x codec: 0x%x output: 0x%x\n", name, in, co, out);

	if (!in || !out) goto fail;

	debug("stream_create() infd: %d outfd: %d\n", in->fd, out->fd);

	if (in->fd == -1) goto fail;

	if (!in->a->control_handler(AUDIO_CONTROL_INIT, AUDIO_READ, in, co, out))		goto fail;
	if (!out->a->control_handler(AUDIO_CONTROL_INIT, AUDIO_WRITE, out, co, in))		goto fail;
	if (co && !co->c->control_handler(AUDIO_CONTROL_INIT, AUDIO_RDWR, co, in, out))		goto fail;

	s = xmalloc(sizeof(stream_t));
	s->stream_name	= xstrdup(name);
	s->input	= in;
	s->codec	= co;
	s->output	= out;

	streams_add(s);

	watch_add(NULL, in->fd, WATCH_READ, stream_handle, s);

	in->buffer	= string_init(NULL);
	out->buffer	= string_init(NULL);

	if (out->fd != -1) {
		watch_t *tmp	= watch_add_line(NULL, out->fd, WATCH_WRITE, stream_handle_write, s);
		tmp->buf	= out->buffer;
	}

	return 1;
fail:

	if (in)		{ in->a->control_handler(AUDIO_CONTROL_DEINIT, AUDIO_READ, in);		if (in->fd != -1) close(in->fd);	xfree(in); }
	if (co)		{ co->c->control_handler(AUDIO_CONTROL_DEINIT, AUDIO_RDWR, co);		;					xfree(co); }
	if (out)	{ out->a->control_handler(AUDIO_CONTROL_DEINIT, AUDIO_WRITE, out);	if (out->fd != -1) close(out->fd);	xfree(out); }
	return 0;
}
