qla2x00_free_queues(struct qla_hw_data *ha)
{
	struct req_que *req;
	struct rsp_que *rsp;
	int cnt;

	for (cnt = 0; cnt < ha->max_req_queues; cnt++) {
		if (!test_bit(cnt, ha->req_qid_map))
			continue;

		req = ha->req_q_map[cnt];
		qla2x00_free_req_que(ha, req);
	}
	kfree(ha->req_q_map);
	ha->req_q_map = NULL;

	for (cnt = 0; cnt < ha->max_rsp_queues; cnt++) {
		if (!test_bit(cnt, ha->rsp_qid_map))
			continue;

		rsp = ha->rsp_q_map[cnt];
		qla2x00_free_rsp_que(ha, rsp);
	}
	kfree(ha->rsp_q_map);
	ha->rsp_q_map = NULL;
}
