pgstat_truncate_restore_counters(PgStat_TableXactStatus *trans)
{
	if (trans->truncated)
	{
		trans->tuples_inserted = trans->inserted_pre_trunc;
		trans->tuples_updated = trans->updated_pre_trunc;
		trans->tuples_deleted = trans->deleted_pre_trunc;
	}
}
