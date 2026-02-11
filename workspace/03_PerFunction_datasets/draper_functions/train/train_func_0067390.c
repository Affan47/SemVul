updateAclDependencies(Oid classId, Oid objectId, int32 objsubId,
					  Oid ownerId, bool isGrant,
					  int noldmembers, Oid *oldmembers,
					  int nnewmembers, Oid *newmembers)
{
	Relation	sdepRel;
	Oid		   *diff;
	int			ndiff,
				i;


	if (isGrant)
		ndiff = getOidListDiff(newmembers, nnewmembers,
							   oldmembers, noldmembers, &diff);
	else
		ndiff = getOidListDiff(oldmembers, noldmembers,
							   newmembers, nnewmembers, &diff);

	if (ndiff > 0)
	{
		sdepRel = heap_open(SharedDependRelationId, RowExclusiveLock);


		for (i = 0; i < ndiff; i++)
		{
			Oid			roleid = diff[i];


			if (roleid == ownerId)
				continue;


			if (isSharedObjectPinned(AuthIdRelationId, roleid, sdepRel))
				continue;

			if (isGrant)
				shdepAddDependency(sdepRel, classId, objectId, objsubId,
								   AuthIdRelationId, roleid,
								   SHARED_DEPENDENCY_ACL);
			else
				shdepDropDependency(sdepRel, classId, objectId, objsubId,
									false,
									AuthIdRelationId, roleid,
									SHARED_DEPENDENCY_ACL);
		}

		heap_close(sdepRel, RowExclusiveLock);
	}

	pfree(diff);
}
