deleteObjectsInList(ObjectAddresses *targetObjects, Relation *depRel,
					int flags)
{
	int			i;


	if (trackDroppedObjectsNeeded() && !(flags & PERFORM_DELETION_INTERNAL))
	{
		for (i = 0; i < targetObjects->numrefs; i++)
		{
			const ObjectAddress *thisobj = &targetObjects->refs[i];
			const ObjectAddressExtra *extra = &targetObjects->extras[i];
			bool		original = false;
			bool		normal = false;

			if (extra->flags & DEPFLAG_ORIGINAL)
				original = true;
			if (extra->flags & DEPFLAG_NORMAL)
				normal = true;
			if (extra->flags & DEPFLAG_REVERSE)
				normal = true;

			if (EventTriggerSupportsObjectClass(getObjectClass(thisobj)))
			{
				EventTriggerSQLDropAddObject(thisobj, original, normal);
			}
		}
	}


	for (i = 0; i < targetObjects->numrefs; i++)
	{
		ObjectAddress *thisobj = targetObjects->refs + i;

		deleteOneObject(thisobj, depRel, flags);
	}
}
