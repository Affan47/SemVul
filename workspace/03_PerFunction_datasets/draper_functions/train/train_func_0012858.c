update_grace_times(struct dquot *q)
{
	time_t now;

	time(&now);
	if (q->dq_dqb.dqb_bsoftlimit && toqb(q->dq_dqb.dqb_curspace) >
			q->dq_dqb.dqb_bsoftlimit) {
		if (!q->dq_dqb.dqb_btime)
			q->dq_dqb.dqb_btime =
				now + q->dq_h->qh_info.dqi_bgrace;
	} else {
		q->dq_dqb.dqb_btime = 0;
	}

	if (q->dq_dqb.dqb_isoftlimit && q->dq_dqb.dqb_curinodes >
			q->dq_dqb.dqb_isoftlimit) {
		if (!q->dq_dqb.dqb_itime)
				q->dq_dqb.dqb_itime =
					now + q->dq_h->qh_info.dqi_igrace;
	} else {
		q->dq_dqb.dqb_itime = 0;
	}
}
