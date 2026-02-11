deleteWhatDependsOn(const ObjectAddress *object,
					bool showNotices)
{
	Relation	depRel;
	ObjectAddresses *targetObjects;
	int			i;


	depRel = heap_open(DependRelationId, RowExclusiveLock);


	AcquireDeletionLock(object, 0);


	targetObjects = new_object_addresses();

	findDependentObjects(object,
						 DEPFLAG_ORIGINAL,
						 NULL,
						 targetObjects,
						 NULL,
						 &depRel);


	reportDependentObjects(targetObjects,
						   DROP_CASCADE,
						   showNotices ? NOTICE : DEBUG2,
						   object);


	for (i = 0; i < targetObjects->numrefs; i++)
	{
		ObjectAddress *thisobj = targetObjects->refs + i;
		ObjectAddressExtra *thisextra = targetObjects->extras + i;

		if (thisextra->flags & DEPFLAG_ORIGINAL)
			continue;


		deleteOneObject(thisobj, &depRel, PERFORM_DELETION_INTERNAL);
	}


	free_object_addresses(targetObjects);

	heap_close(depRel, RowExclusiveLock);
}
