RelationIdGetRelation(Oid relationId)
{
	Relation	rd;


	RelationIdCacheLookup(relationId, rd);

	if (RelationIsValid(rd))
	{
		RelationIncrementReferenceCount(rd);

		if (!rd->rd_isvalid)
		{


			if (rd->rd_rel->relkind == RELKIND_INDEX)
				RelationReloadClassinfo(rd);
			else
				RelationClearRelation(rd, true);
		}
		return rd;
	}


	rd = RelationBuildDesc(relationId, true);
	if (RelationIsValid(rd))
		RelationIncrementReferenceCount(rd);
	return rd;
}
