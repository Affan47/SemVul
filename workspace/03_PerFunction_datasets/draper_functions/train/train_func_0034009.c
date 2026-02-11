http_chunk_append_file(server *srv, connection *con, buffer *fn, off_t offset, off_t len) {
	chunkqueue *cq;

	if (!con) return -1;

	cq = con->write_queue;


	chunkqueue_append_file(cq, fn, offset, len);

	return 0;
}
