lastval(PG_FUNCTION_ARGS)
{
	Relation	seqrel;
	int64		result;

	if (last_used_seq == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("lastval is not yet defined in this session")));


	if (!SearchSysCacheExists(RELOID,
							  ObjectIdGetDatum(last_used_seq->relid),
							  0, 0, 0))
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("lastval is not yet defined in this session")));

	seqrel = open_share_lock(last_used_seq);


	Assert(last_used_seq->last_valid);

	if (pg_class_aclcheck(last_used_seq->relid, GetUserId(), ACL_SELECT) != ACLCHECK_OK &&
		pg_class_aclcheck(last_used_seq->relid, GetUserId(), ACL_USAGE) != ACLCHECK_OK)
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied for sequence %s",
						RelationGetRelationName(seqrel))));

	result = last_used_seq->last;
	relation_close(seqrel, NoLock);

	PG_RETURN_INT64(result);
}
