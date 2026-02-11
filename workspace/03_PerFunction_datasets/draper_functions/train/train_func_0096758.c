conn_plain_write(conn_t * conn, void *data, size_t len)
{
	if(IsDead(conn))
		return;
	rb_rawbuf_append(conn->plainbuf_out, data, len);
}
