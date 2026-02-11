updateAclDependencies(Oid classId, Oid objectId, int32 objsubId,
					  Oid ownerId,
					  int noldmembers, Oid *oldmembers,
					  int nnewmembers, Oid *newmembers)
{
	Relation	sdepRel;
	int			i;


	getOidListDiff(oldmembers, &noldmembers, newmembers, &nnewmembers);

	if (noldmembers > 0 || nnewmembers > 0)
	{
		sdepRel = heap_open(SharedDependRelationId, RowExclusiveLock);


		for (i = 0; i < nnewmembers; i++)
		{
			Oid			roleid = newmembers[i];


			if (roleid == ownerId)
				continue;


			if (isSharedObjectPinned(AuthIdRelationId, roleid, sdepRel))
				continue;

			shdepAddDependency(sdepRel, classId, objectId, objsubId,
							   AuthIdRelationId, roleid,
							   SHARED_DEPENDENCY_ACL);
		}


		for (i = 0; i < noldmembers; i++)
		{
			Oid			roleid = oldmembers[i];


			if (roleid == ownerId)
				continue;


			if (isSharedObjectPinned(AuthIdRelationId, roleid, sdepRel))
				continue;

			shdepDropDependency(sdepRel, classId, objectId, objsubId,
								false,
								AuthIdRelationId, roleid,
								SHARED_DEPENDENCY_ACL);
		}

		heap_close(sdepRel, RowExclusiveLock);
	}

	if (oldmembers)
		pfree(oldmembers);
	if (newmembers)
		pfree(newmembers);
}
