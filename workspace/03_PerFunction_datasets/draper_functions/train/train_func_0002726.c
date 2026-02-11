dispose_chunk( conn_t *conn )
{
	buff_chunk_t *bc = conn->write_buf;
	if (!(conn->write_buf = bc->next))
		conn->write_buf_append = &conn->write_buf;
	if (bc->data != bc->buf)
		free( bc->data );
	free( bc );
}
