GetComboCommandId(CommandId cmin, CommandId cmax)
{
	CommandId	combocid;
	ComboCidKeyData key;
	ComboCidEntry entry;
	bool		found;


	if (comboHash == NULL)
	{
		HASHCTL		hash_ctl;

		memset(&hash_ctl, 0, sizeof(hash_ctl));
		hash_ctl.keysize = sizeof(ComboCidKeyData);
		hash_ctl.entrysize = sizeof(ComboCidEntryData);
		hash_ctl.hcxt = TopTransactionContext;

		comboHash = hash_create("Combo CIDs",
								CCID_HASH_SIZE,
								&hash_ctl,
								HASH_ELEM | HASH_BLOBS | HASH_CONTEXT);

		comboCids = (ComboCidKeyData *)
			MemoryContextAlloc(TopTransactionContext,
							   sizeof(ComboCidKeyData) * CCID_ARRAY_SIZE);
		sizeComboCids = CCID_ARRAY_SIZE;
		usedComboCids = 0;
	}


	key.cmin = cmin;
	key.cmax = cmax;
	entry = (ComboCidEntry) hash_search(comboHash,
										(void *) &key,
										HASH_ENTER,
										&found);

	if (found)
	{

		return entry->combocid;
	}


	if (usedComboCids >= sizeComboCids)
	{

		int			newsize = sizeComboCids * 2;

		comboCids = (ComboCidKeyData *)
			repalloc(comboCids, sizeof(ComboCidKeyData) * newsize);
		sizeComboCids = newsize;
	}

	combocid = usedComboCids;

	comboCids[combocid].cmin = cmin;
	comboCids[combocid].cmax = cmax;
	usedComboCids++;

	entry->combocid = combocid;

	return combocid;
}
