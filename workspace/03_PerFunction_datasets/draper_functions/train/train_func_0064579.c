dquot_mark_dquot_dirty(struct dquot *dquot)
{
	int ret = 1;


	if (test_bit(DQ_MOD_B, &dquot->dq_flags))
		return 1;

	spin_lock(&dq_list_lock);
	if (!test_and_set_bit(DQ_MOD_B, &dquot->dq_flags)) {
		list_add(&dquot->dq_dirty, &sb_dqopt(dquot->dq_sb)->
				info[dquot->dq_id.type].dqi_dirty_list);
		ret = 0;
	}
	spin_unlock(&dq_list_lock);
	return ret;
}
