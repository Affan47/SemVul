RelationInitLockInfo(Relation relation)
{
	Assert(RelationIsValid(relation));
	Assert(OidIsValid(RelationGetRelid(relation)));

	relation->rd_lockInfo.lockRelId.relId = RelationGetRelid(relation);

	if (relation->rd_rel->relisshared)
		relation->rd_lockInfo.lockRelId.dbId = InvalidOid;
	else
		relation->rd_lockInfo.lockRelId.dbId = MyDatabaseId;
}
