ggep_stream_packv(ggep_stream_t *gs,
	const char *id, const iovec_t *iov, int iovcnt, uint32 wflags)
{
	g_assert(iovcnt >= 0);

	if (!ggep_stream_begin(gs, id, wflags))
		return FALSE;

	if (!ggep_stream_writev(gs, iov, iovcnt))
		return FALSE;

	if (!ggep_stream_end(gs))
		return FALSE;

	return TRUE;
}
