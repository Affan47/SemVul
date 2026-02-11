AtAbort_Portals(void)
{
	HASH_SEQ_STATUS status;
	PortalHashEnt *hentry;

	hash_seq_init(&status, PortalHashTable);

	while ((hentry = (PortalHashEnt *) hash_seq_search(&status)) != NULL)
	{
		Portal		portal = hentry->portal;

		if (portal->status == PORTAL_ACTIVE)
			portal->status = PORTAL_FAILED;


		if (portal->createSubid == InvalidSubTransactionId)
			continue;


		if (PointerIsValid(portal->cleanup))
		{
			(*portal->cleanup) (portal);
			portal->cleanup = NULL;
		}


		portal->resowner = NULL;


		MemoryContextDeleteChildren(PortalGetHeapMemory(portal));
	}
}
