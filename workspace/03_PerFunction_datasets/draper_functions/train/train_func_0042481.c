qd_check_sync(struct gfs2_sbd *sdp, struct gfs2_quota_data *qd,
			 u64 *sync_gen)
{
	if (test_bit(QDF_LOCKED, &qd->qd_flags) ||
	    !test_bit(QDF_CHANGE, &qd->qd_flags) ||
	    (sync_gen && (qd->qd_sync_gen >= *sync_gen)))
		return 0;

	if (!lockref_get_not_dead(&qd->qd_lockref))
		return 0;

	list_move_tail(&qd->qd_list, &sdp->sd_quota_list);
	set_bit(QDF_LOCKED, &qd->qd_flags);
	qd->qd_change_sync = qd->qd_change;
	slot_hold(qd);
	return 1;
}
