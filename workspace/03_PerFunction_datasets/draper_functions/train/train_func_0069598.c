socket_free_buffer(struct gnutella_socket *s)
{
	socket_buffer_check(s);

	if (NULL != s->buf) {
		s->buf_size = 0;
		HFREE_NULL(s->buf);
		s->pos = 0;
	}
}
