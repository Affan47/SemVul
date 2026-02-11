qib7322_alloc_send_buf ( struct qib7322 *qib7322,
				    struct qib7322_send_buffers *send_bufs ) {
	unsigned int used;
	unsigned int mask;
	unsigned int send_buf;

	used = ( send_bufs->cons - send_bufs->prod );
	if ( used >= send_bufs->count ) {
		DBGC ( qib7322, "QIB7322 %p send buffer set %p out of "
		       "buffers\n", qib7322, send_bufs );
		return -ENOBUFS;
	}

	mask = ( send_bufs->count - 1 );
	send_buf = send_bufs->avail[ send_bufs->cons++ & mask ];
	send_buf ^= QIB7322_SEND_BUF_TOGGLE;
	return send_buf;
}
