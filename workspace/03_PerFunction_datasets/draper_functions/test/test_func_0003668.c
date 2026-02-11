forget_invalid_pages(RelFileNode node, BlockNumber minblkno)
{
	HASH_SEQ_STATUS status;
	xl_invalid_page *hentry;

	if (invalid_page_tab == NULL)
		return;

	hash_seq_init(&status, invalid_page_tab);

	while ((hentry = (xl_invalid_page *) hash_seq_search(&status)) != NULL)
	{
		if (RelFileNodeEquals(hentry->key.node, node) &&
			hentry->key.blkno >= minblkno)
		{
			elog(DEBUG2, "page %u of relation %u/%u/%u has been dropped",
				 hentry->key.blkno, hentry->key.node.spcNode,
				 hentry->key.node.dbNode, hentry->key.node.relNode);

			if (hash_search(invalid_page_tab,
							(void *) &hentry->key,
							HASH_REMOVE, NULL) == NULL)
				elog(ERROR, "hash table corrupted");
		}
	}
}
