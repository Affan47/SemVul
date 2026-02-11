tbuf_read(int fd, size_t len)
{
	g_assert(fd >= 0);

	TBUF_INIT_READ(len);

	return read(fd, tbuf.arena, len);
}
