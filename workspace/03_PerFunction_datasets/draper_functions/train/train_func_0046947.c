dquot_reclaim_reserved_space(struct dquot *dquot, qsize_t number)
{
	if (WARN_ON_ONCE(dquot->dq_dqb.dqb_curspace < number))
		number = dquot->dq_dqb.dqb_curspace;
	dquot->dq_dqb.dqb_rsvspace += number;
	dquot->dq_dqb.dqb_curspace -= number;
}
