info_idq_free(struct dquot *dquot, qsize_t inodes)
{
	qsize_t newinodes;

	if (test_bit(DQ_FAKE_B, &dquot->dq_flags) ||
	    dquot->dq_dqb.dqb_curinodes <= dquot->dq_dqb.dqb_isoftlimit ||
	    !sb_has_quota_limits_enabled(dquot->dq_sb, dquot->dq_id.type))
		return QUOTA_NL_NOWARN;

	newinodes = dquot->dq_dqb.dqb_curinodes - inodes;
	if (newinodes <= dquot->dq_dqb.dqb_isoftlimit)
		return QUOTA_NL_ISOFTBELOW;
	if (dquot->dq_dqb.dqb_curinodes >= dquot->dq_dqb.dqb_ihardlimit &&
	    newinodes < dquot->dq_dqb.dqb_ihardlimit)
		return QUOTA_NL_IHARDBELOW;
	return QUOTA_NL_NOWARN;
}
