tbm_create_pagetable(TIDBitmap *tbm)
{
	HASHCTL		hash_ctl;

	Assert(tbm->status != TBM_HASH);
	Assert(tbm->pagetable == NULL);


	MemSet(&hash_ctl, 0, sizeof(hash_ctl));
	hash_ctl.keysize = sizeof(BlockNumber);
	hash_ctl.entrysize = sizeof(PagetableEntry);
	hash_ctl.hcxt = tbm->mcxt;
	tbm->pagetable = hash_create("TIDBitmap",
								 128,
								 &hash_ctl,
								 HASH_ELEM | HASH_BLOBS | HASH_CONTEXT);


	if (tbm->status == TBM_ONE_PAGE)
	{
		PagetableEntry *page;
		bool		found;

		page = (PagetableEntry *) hash_search(tbm->pagetable,
											  (void *) &tbm->entry1.blockno,
											  HASH_ENTER, &found);
		Assert(!found);
		memcpy(page, &tbm->entry1, sizeof(PagetableEntry));
	}

	tbm->status = TBM_HASH;
}
