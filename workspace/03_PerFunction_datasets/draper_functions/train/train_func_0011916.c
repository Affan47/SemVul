zlib_process(mod_ctl_t * ctl, mod_ctl_buf_t * ctlb)
{
	uint8_t level;
	size_t recvqlen;
	size_t hdr = (sizeof(uint8_t) * 2) + sizeof(int32_t);
	void *recvq_start;
	z_stream *instream, *outstream;
	conn_t *conn;
	int32_t id;

	conn = make_conn(ctl, ctlb->F[0], ctlb->F[1]);

	if(conn == NULL)
	{
		rb_close(ctlb->F[0]);
		rb_close(ctlb->F[1]);
		return;
	}


	if(rb_get_type(conn->mod_fd) == RB_FD_UNKNOWN)
		rb_set_type(conn->mod_fd, RB_FD_SOCKET);

	if(rb_get_type(conn->plain_fd) == RB_FD_UNKNOWN)
		rb_set_type(conn->plain_fd, RB_FD_SOCKET);

	id = buf_to_int32(&ctlb->buf[1]);
	conn_add_id_hash(conn, id);

	level = (uint8_t)ctlb->buf[5];

	recvqlen = ctlb->buflen - hdr;
	recvq_start = &ctlb->buf[6];

	SetZip(conn);
	conn->stream = rb_malloc(sizeof(zlib_stream_t));
	instream = &((zlib_stream_t *) conn->stream)->instream;
	outstream = &((zlib_stream_t *) conn->stream)->outstream;

	instream->total_in = 0;
	instream->total_out = 0;
	instream->zalloc = (alloc_func) ssld_alloc;
	instream->zfree = (free_func) ssld_free;
	instream->data_type = Z_ASCII;
	inflateInit(&((zlib_stream_t *) conn->stream)->instream);

	outstream->total_in = 0;
	outstream->total_out = 0;
	outstream->zalloc = (alloc_func) ssld_alloc;
	outstream->zfree = (free_func) ssld_free;
	outstream->data_type = Z_ASCII;

	if(level > 9)
		level = Z_DEFAULT_COMPRESSION;

	deflateInit(&((zlib_stream_t *) conn->stream)->outstream, level);
	if(recvqlen > 0)
		common_zlib_inflate(conn, recvq_start, recvqlen);

	conn_mod_read_cb(conn->mod_fd, conn);
	conn_plain_read_cb(conn->plain_fd, conn);
	return;

}
