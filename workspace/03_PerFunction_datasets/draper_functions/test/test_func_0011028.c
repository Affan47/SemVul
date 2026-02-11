bnx2x_vf_queue_create(struct bnx2x *bp,
				 struct bnx2x_virtf *vf, int qid,
				 struct bnx2x_vf_queue_construct_params *qctor)
{
	struct bnx2x_queue_state_params *q_params;
	int rc = 0;

	DP(BNX2X_MSG_IOV, "vf[%d:%d]\n", vf->abs_vfid, qid);


	q_params = &qctor->qstate;
	q_params->q_obj = &bnx2x_vfq(vf, qid, sp_obj);
	set_bit(RAMROD_COMP_WAIT, &q_params->ramrod_flags);

	if (bnx2x_get_q_logical_state(bp, q_params->q_obj) ==
	    BNX2X_Q_LOGICAL_STATE_ACTIVE) {
		DP(BNX2X_MSG_IOV, "queue was already up. Aborting gracefully\n");
		goto out;
	}


	q_params->cmd = BNX2X_Q_CMD_INIT;
	rc = bnx2x_queue_state_change(bp, q_params);
	if (rc)
		goto out;

	memcpy(&q_params->params.setup, &qctor->prep_qsetup,
	       sizeof(struct bnx2x_queue_setup_params));
	q_params->cmd = BNX2X_Q_CMD_SETUP;
	rc = bnx2x_queue_state_change(bp, q_params);
	if (rc)
		goto out;


	bnx2x_vf_igu_ack_sb(bp, vf, vf_igu_sb(vf, bnx2x_vfq(vf, qid, sb_idx)),
			    USTORM_ID, 0, IGU_INT_ENABLE, 0);
out:
	return rc;
}
