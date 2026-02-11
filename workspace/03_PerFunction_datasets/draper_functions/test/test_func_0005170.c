ib_complete_recv ( struct ib_device *ibdev, struct ib_queue_pair *qp,
			struct ib_address_vector *dest,
			struct ib_address_vector *source,
			struct io_buffer *iobuf, int rc ) {

	if ( qp->recv.cq->op->complete_recv ) {
		qp->recv.cq->op->complete_recv ( ibdev, qp, dest, source,
						 iobuf, rc );
	} else {
		free_iob ( iobuf );
	}
	qp->recv.fill--;
}
