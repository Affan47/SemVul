arbel_destroy_qp ( struct ib_device *ibdev,
			       struct ib_queue_pair *qp ) {
	struct arbel *arbel = ib_get_drvdata ( ibdev );
	struct arbel_queue_pair *arbel_qp = ib_qp_get_drvdata ( qp );
	struct arbelprm_qp_db_record *send_db_rec;
	struct arbelprm_qp_db_record *recv_db_rec;
	int qpn_offset;
	int rc;


	if ( ( rc = arbel_cmd_2rst_qpee ( arbel, qp->qpn ) ) != 0 ) {
		DBGC ( arbel, "Arbel %p FATAL 2RST_QPEE failed on QPN %#lx: "
		       "%s\n", arbel, qp->qpn, strerror ( rc ) );

		return;
	}


	send_db_rec = &arbel->db_rec[arbel_qp->send.doorbell_idx].qp;
	recv_db_rec = &arbel->db_rec[arbel_qp->recv.doorbell_idx].qp;
	MLX_FILL_1 ( send_db_rec, 1, res, ARBEL_UAR_RES_NONE );
	MLX_FILL_1 ( recv_db_rec, 1, res, ARBEL_UAR_RES_NONE );


	free_dma ( arbel_qp->send.wqe, arbel_qp->send.wqe_size );
	free_dma ( arbel_qp->recv.wqe, arbel_qp->recv.wqe_size );
	free ( arbel_qp );


	qpn_offset = ( qp->qpn - ARBEL_QPN_BASE - arbel->limits.reserved_qps );
	arbel_free_qn_offset ( arbel->qp_inuse, qpn_offset );

	ib_qp_set_drvdata ( qp, NULL );
}
