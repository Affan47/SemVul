renameatt(RenameStmt *stmt)
{
	Oid			relid;
	AttrNumber	attnum;
	ObjectAddress address;


	relid = RangeVarGetRelidExtended(stmt->relation, AccessExclusiveLock,
									 stmt->missing_ok, false,
									 RangeVarCallbackForRenameAttribute,
									 NULL);

	if (!OidIsValid(relid))
	{
		ereport(NOTICE,
				(errmsg("relation \"%s\" does not exist, skipping",
						stmt->relation->relname)));
		return InvalidObjectAddress;
	}

	attnum =
		renameatt_internal(relid,
						   stmt->subname,
						   stmt->newname,
						   interpretInhOption(stmt->relation->inhOpt),
						   false,
						   0,
						   stmt->behavior);

	ObjectAddressSubSet(address, RelationRelationId, relid, attnum);

	return address;
}
