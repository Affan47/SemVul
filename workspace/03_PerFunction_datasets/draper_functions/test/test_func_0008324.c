qed_send_qm_stop_cmd(struct qed_hwfn *p_hwfn,
			  struct qed_ptt *p_ptt,
			  bool is_release_cmd,
			  bool is_tx_pq,
			  u16 start_pq,
			  u16 num_pqs)
{
	u32 cmd_arr[QM_CMD_STRUCT_SIZE(QM_STOP_CMD)] = { 0 };
	u32 pq_mask = 0, last_pq = start_pq + num_pqs - 1, pq_id;


	QM_CMD_SET_FIELD(cmd_arr, QM_STOP_CMD, PQ_TYPE, is_tx_pq ? 0 : 1);

	for (pq_id = start_pq; pq_id <= last_pq; pq_id++) {

		if (!is_release_cmd)
			pq_mask |= (1 << (pq_id % QM_STOP_PQ_MASK_WIDTH));


		if ((pq_id == last_pq) ||
		    (pq_id % QM_STOP_PQ_MASK_WIDTH ==
		     (QM_STOP_PQ_MASK_WIDTH - 1))) {
			QM_CMD_SET_FIELD(cmd_arr, QM_STOP_CMD,
					 PAUSE_MASK, pq_mask);
			QM_CMD_SET_FIELD(cmd_arr, QM_STOP_CMD,
					 GROUP_ID,
					 pq_id / QM_STOP_PQ_MASK_WIDTH);
			if (!qed_send_qm_cmd(p_hwfn, p_ptt, QM_STOP_CMD_ADDR,
					     cmd_arr[0], cmd_arr[1]))
				return false;
			pq_mask = 0;
		}
	}

	return true;
}
