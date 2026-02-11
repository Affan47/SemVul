ginRedoInsert(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	ginxlogInsert *data = (ginxlogInsert *) XLogRecGetData(record);
	Buffer		buffer;
#ifdef NOT_USED
	BlockNumber leftChildBlkno = InvalidBlockNumber;
#endif
	BlockNumber rightChildBlkno = InvalidBlockNumber;
	bool		isLeaf = (data->flags & GIN_INSERT_ISLEAF) != 0;


	if (!isLeaf)
	{
		char	   *payload = XLogRecGetData(record) + sizeof(ginxlogInsert);

#ifdef NOT_USED
		leftChildBlkno = BlockIdGetBlockNumber((BlockId) payload);
#endif
		payload += sizeof(BlockIdData);
		rightChildBlkno = BlockIdGetBlockNumber((BlockId) payload);
		payload += sizeof(BlockIdData);

		ginRedoClearIncompleteSplit(record, 1);
	}

	if (XLogReadBufferForRedo(record, 0, &buffer) == BLK_NEEDS_REDO)
	{
		Page		page = BufferGetPage(buffer);
		Size		len;
		char	   *payload = XLogRecGetBlockData(record, 0, &len);


		if (data->flags & GIN_INSERT_ISDATA)
		{
			Assert(GinPageIsData(page));
			ginRedoInsertData(buffer, isLeaf, rightChildBlkno, payload);
		}
		else
		{
			Assert(!GinPageIsData(page));
			ginRedoInsertEntry(buffer, isLeaf, rightChildBlkno, payload);
		}

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}
	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);
}
