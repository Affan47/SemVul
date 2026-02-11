qib7322_post_recv ( struct ib_device *ibdev,
			       struct ib_queue_pair *qp,
			       struct io_buffer *iobuf ) {
	struct qib7322 *qib7322 = ib_get_drvdata ( ibdev );
	struct ib_work_queue *wq = &qp->recv;
	struct qib7322_recv_work_queue *qib7322_wq = ib_wq_get_drvdata ( wq );
	struct QIB_7322_RcvEgr rcvegr;
	struct QIB_7322_scalar rcvegrindexhead;
	unsigned int ctx = qib7322_ctx ( ibdev, qp );
	physaddr_t addr;
	size_t len;
	unsigned int wqe_idx;
	unsigned int bufsize;


	addr = virt_to_bus ( iobuf->data );
	len = iob_tailroom ( iobuf );
	if ( addr & ( QIB7322_EAGER_BUFFER_ALIGN - 1 ) ) {
		DBGC ( qib7322, "QIB7322 %p QPN %ld misaligned RX buffer "
		       "(%08lx)\n", qib7322, qp->qpn, addr );
		return -EINVAL;
	}
	if ( len != QIB7322_RECV_PAYLOAD_SIZE ) {
		DBGC ( qib7322, "QIB7322 %p QPN %ld wrong RX buffer size "
		       "(%zd)\n", qib7322, qp->qpn, len );
		return -EINVAL;
	}


	wqe_idx = ( qib7322_wq->eager_prod & ( wq->num_wqes - 1 ) );
	assert ( wq->iobufs[wqe_idx] == NULL );


	wq->iobufs[wqe_idx] = iobuf;


	switch ( QIB7322_RECV_PAYLOAD_SIZE ) {
	case 2048:  bufsize = QIB7322_EAGER_BUFFER_2K;  break;
	case 4096:  bufsize = QIB7322_EAGER_BUFFER_4K;  break;
	case 8192:  bufsize = QIB7322_EAGER_BUFFER_8K;  break;
	case 16384: bufsize = QIB7322_EAGER_BUFFER_16K; break;
	case 32768: bufsize = QIB7322_EAGER_BUFFER_32K; break;
	case 65536: bufsize = QIB7322_EAGER_BUFFER_64K; break;
	default:    linker_assert ( 0, invalid_rx_payload_size );
		    bufsize = QIB7322_EAGER_BUFFER_NONE;
	}


	memset ( &rcvegr, 0, sizeof ( rcvegr ) );
	BIT_FILL_2 ( &rcvegr,
		     Addr, ( addr >> 11 ),
		     BufSize, bufsize );
	qib7322_writeq_array8b ( qib7322, &rcvegr, qib7322_wq->eager_array,
				 qib7322_wq->eager_prod );
	DBGC2 ( qib7322, "QIB7322 %p QPN %ld RX egr %04x(%04x) posted "
		"[%lx,%lx)\n", qib7322, qp->qpn, qib7322_wq->eager_prod,
		wqe_idx, addr, ( addr + len ) );


	qib7322_wq->eager_prod = ( ( qib7322_wq->eager_prod + 1 ) &
				   ( qib7322_wq->eager_entries - 1 ) );


	memset ( &rcvegrindexhead, 0, sizeof ( rcvegrindexhead ) );
	BIT_FILL_1 ( &rcvegrindexhead,
		     Value, ( ( qib7322_wq->eager_prod + 1 ) &
			      ( qib7322_wq->eager_entries - 1 ) ) );
	qib7322_writeq_array64k ( qib7322, &rcvegrindexhead,
				  QIB_7322_RcvEgrIndexHead0_offset, ctx );

	return 0;
}
