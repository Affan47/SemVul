qib7322_post_send ( struct ib_device *ibdev,
			       struct ib_queue_pair *qp,
			       struct ib_address_vector *dest,
			       struct io_buffer *iobuf ) {
	struct qib7322 *qib7322 = ib_get_drvdata ( ibdev );
	struct ib_work_queue *wq = &qp->send;
	struct qib7322_send_work_queue *qib7322_wq = ib_wq_get_drvdata ( wq );
	struct QIB_7322_SendPbc sendpbc;
	unsigned int port = ( ibdev->port - QIB7322_PORT_BASE );
	uint8_t header_buf[IB_MAX_HEADER_SIZE];
	struct io_buffer headers;
	int send_buf;
	unsigned long start_offset;
	unsigned long offset;
	size_t len;
	ssize_t frag_len;
	uint32_t *data;


	send_buf = qib7322_alloc_send_buf ( qib7322, qib7322_wq->send_bufs );
	if ( send_buf < 0 )
		return send_buf;
	start_offset = offset =
		qib7322_send_buffer_offset ( qib7322, qib7322_wq->send_bufs,
					     send_buf );


	assert ( wq->iobufs[qib7322_wq->prod] == NULL );
	wq->iobufs[qib7322_wq->prod] = iobuf;
	qib7322_wq->used[qib7322_wq->prod] = send_buf;


	iob_populate ( &headers, header_buf, 0, sizeof ( header_buf ) );
	iob_reserve ( &headers, sizeof ( header_buf ) );
	ib_push ( ibdev, &headers, qp, iob_len ( iobuf ), dest );


	len = ( ( sizeof ( sendpbc ) + iob_len ( &headers ) +
		  iob_len ( iobuf ) + 3 ) & ~3 );


	memset ( &sendpbc, 0, sizeof ( sendpbc ) );
	BIT_FILL_3 ( &sendpbc,
		     LengthP1_toibc, ( ( len >> 2 ) - 1 ),
		     Port, port,
		     VL15, ( ( qp->type == IB_QPT_SMI ) ? 1 : 0 ) );


	DBG_DISABLE ( DBGLVL_IO );
	qib7322_writeq ( qib7322, &sendpbc, offset );
	offset += sizeof ( sendpbc );


	for ( data = headers.data, frag_len = iob_len ( &headers ) ;
	      frag_len > 0 ; data++, offset += 4, frag_len -= 4 ) {
		qib7322_writel ( qib7322, *data, offset );
	}


	for ( data = iobuf->data, frag_len = iob_len ( iobuf ) ;
	      frag_len > 0 ; data++, offset += 4, frag_len -= 4 ) {
		qib7322_writel ( qib7322, *data, offset );
	}
	DBG_ENABLE ( DBGLVL_IO );

	assert ( ( start_offset + len ) == offset );
	DBGC2 ( qib7322, "QIB7322 %p QPN %ld TX %04x(%04x) posted [%lx,%lx)\n",
		qib7322, qp->qpn, send_buf, qib7322_wq->prod,
		start_offset, offset );


	qib7322_wq->prod = ( ( qib7322_wq->prod + 1 ) & ( wq->num_wqes - 1 ) );

	return 0;
}
