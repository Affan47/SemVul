hermon_destroy_cq ( struct ib_device *ibdev,
				struct ib_completion_queue *cq ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	struct hermon_completion_queue *hermon_cq = ib_cq_get_drvdata ( cq );
	struct hermonprm_completion_queue_context cqctx;
	int cqn_offset;
	int rc;


	if ( ( rc = hermon_cmd_hw2sw_cq ( hermon, cq->cqn, &cqctx ) ) != 0 ) {
		DBGC ( hermon, "Hermon %p FATAL HW2SW_CQ failed on CQN %#lx: "
		       "%s\n", hermon, cq->cqn, strerror ( rc ) );

		return;
	}


	hermon_free_mtt ( hermon, &hermon_cq->mtt );


	free_dma ( hermon_cq->cqe, hermon_cq->cqe_size );
	free ( hermon_cq );


	cqn_offset = ( cq->cqn - hermon->cap.reserved_cqs );
	hermon_bitmask_free ( hermon->cq_inuse, cqn_offset, 1 );

	ib_cq_set_drvdata ( cq, NULL );
}
