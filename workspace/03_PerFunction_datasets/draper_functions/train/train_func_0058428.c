log_invalid_page(RelFileNode node, BlockNumber blkno, bool present)
{
	xl_invalid_page_key key;
	xl_invalid_page *hentry;
	bool		found;


	if (present)
		elog(DEBUG1, "page %u of relation %u/%u/%u is uninitialized",
			 blkno, node.spcNode, node.dbNode, node.relNode);
	else
		elog(DEBUG1, "page %u of relation %u/%u/%u does not exist",
			 blkno, node.spcNode, node.dbNode, node.relNode);

	if (invalid_page_tab == NULL)
	{

		HASHCTL		ctl;

		memset(&ctl, 0, sizeof(ctl));
		ctl.keysize = sizeof(xl_invalid_page_key);
		ctl.entrysize = sizeof(xl_invalid_page);
		ctl.hash = tag_hash;

		invalid_page_tab = hash_create("XLOG invalid-page table",
									   100,
									   &ctl,
									   HASH_ELEM | HASH_FUNCTION);
	}


	key.node = node;
	key.blkno = blkno;
	hentry = (xl_invalid_page *)
		hash_search(invalid_page_tab, (void *) &key, HASH_ENTER, &found);

	if (!found)
	{

		hentry->present = present;
	}
	else
	{

	}
}
