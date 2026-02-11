gfs2_quota_refresh(struct gfs2_sbd *sdp, struct kqid qid)
{
	struct gfs2_quota_data *qd;
	struct gfs2_holder q_gh;
	int error;

	error = qd_get(sdp, qid, &qd);
	if (error)
		return error;

	error = do_glock(qd, FORCE, &q_gh);
	if (!error)
		gfs2_glock_dq_uninit(&q_gh);

	qd_put(qd);
	return error;
}
