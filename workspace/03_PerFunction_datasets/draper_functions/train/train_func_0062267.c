hermon_post_recv ( struct ib_device *ibdev,
			      struct ib_queue_pair *qp,
			      struct io_buffer *iobuf ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	struct hermon_queue_pair *hermon_qp = ib_qp_get_drvdata ( qp );
	struct ib_work_queue *wq = &qp->recv;
	struct hermon_recv_work_queue *hermon_recv_wq = &hermon_qp->recv;
	struct hermonprm_recv_wqe *wqe;
	unsigned int wqe_idx_mask;


	wqe_idx_mask = ( wq->num_wqes - 1 );
	if ( wq->iobufs[wq->next_idx & wqe_idx_mask] ) {
		DBGC ( hermon, "Hermon %p receive queue full", hermon );
		return -ENOBUFS;
	}
	wq->iobufs[wq->next_idx & wqe_idx_mask] = iobuf;
	wqe = &hermon_recv_wq->wqe[wq->next_idx & wqe_idx_mask].recv;


	MLX_FILL_1 ( &wqe->data[0], 0, byte_count, iob_tailroom ( iobuf ) );
	MLX_FILL_1 ( &wqe->data[0], 1, l_key, hermon->lkey );
	MLX_FILL_1 ( &wqe->data[0], 3,
		     local_address_l, virt_to_bus ( iobuf->data ) );


	wq->next_idx++;


	barrier();
	MLX_FILL_1 ( &hermon_recv_wq->doorbell, 0, receive_wqe_counter,
		     ( wq->next_idx & 0xffff ) );

	return 0;
}
