AtSubAbort_Portals(SubTransactionId mySubid,
				   SubTransactionId parentSubid,
				   ResourceOwner parentXactOwner)
{
	HASH_SEQ_STATUS status;
	PortalHashEnt *hentry;

	hash_seq_init(&status, PortalHashTable);

	while ((hentry = (PortalHashEnt *) hash_seq_search(&status)) != NULL)
	{
		Portal		portal = hentry->portal;

		if (portal->createSubid != mySubid)
			continue;


		if (portal->status == PORTAL_ACTIVE)
			portal->status = PORTAL_FAILED;


#ifdef NOT_USED
		if (portal->status == PORTAL_READY)
		{
			portal->createSubid = parentSubid;
			if (portal->resowner)
				ResourceOwnerNewParent(portal->resowner, parentXactOwner);
		}
		else
#endif
		{

			if (PointerIsValid(portal->cleanup))
			{
				(*portal->cleanup) (portal);
				portal->cleanup = NULL;
			}


			portal->resowner = NULL;


			MemoryContextDeleteChildren(PortalGetHeapMemory(portal));
		}
	}
}
