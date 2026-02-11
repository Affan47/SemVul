qib7322_destroy_recv_wq ( struct ib_device *ibdev,
				      struct ib_queue_pair *qp ) {
	struct qib7322 *qib7322 = ib_get_drvdata ( ibdev );
	struct ib_work_queue *wq = &qp->recv;
	struct qib7322_recv_work_queue *qib7322_wq = ib_wq_get_drvdata ( wq );
	struct QIB_7322_RcvCtrl rcvctrl;
	struct QIB_7322_RcvCtrl_P rcvctrlp;
	unsigned int port = ( ibdev->port - QIB7322_PORT_BASE );
	unsigned int ctx = qib7322_ctx ( ibdev, qp );


	qib7322_readq_port ( qib7322, &rcvctrlp,
			     QIB_7322_RcvCtrl_0_offset, port );
	BIT_SET ( &rcvctrlp, ContextEnable[ctx], 0 );
	qib7322_writeq_port ( qib7322, &rcvctrlp,
			      QIB_7322_RcvCtrl_0_offset, port );
	qib7322_readq ( qib7322, &rcvctrl, QIB_7322_RcvCtrl_offset );
	BIT_SET ( &rcvctrl, IntrAvail[ctx], 0 );
	qib7322_writeq ( qib7322, &rcvctrl, QIB_7322_RcvCtrl_offset );


	qib7322_readq ( qib7322, &rcvctrl, QIB_7322_RcvCtrl_offset );
	mb();


	free_dma ( qib7322_wq->header, QIB7322_RECV_HEADERS_SIZE );
}
