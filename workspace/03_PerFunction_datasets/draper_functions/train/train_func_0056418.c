ExecHashTableInsert(HashJoinTable hashtable,
					TupleTableSlot *slot,
					uint32 hashvalue)
{
	MinimalTuple tuple = ExecFetchSlotMinimalTuple(slot);
	int			bucketno;
	int			batchno;

	ExecHashGetBucketAndBatch(hashtable, hashvalue,
							  &bucketno, &batchno);


	if (batchno == hashtable->curbatch)
	{


		HashJoinTuple hashTuple;
		int			hashTupleSize;

		hashTupleSize = HJTUPLE_OVERHEAD + tuple->t_len;
		hashTuple = (HashJoinTuple) MemoryContextAlloc(hashtable->batchCxt,
													   hashTupleSize);
		hashTuple->hashvalue = hashvalue;
		memcpy(HJTUPLE_MINTUPLE(hashTuple), tuple, tuple->t_len);
		hashTuple->next = hashtable->buckets[bucketno];
		hashtable->buckets[bucketno] = hashTuple;
		hashtable->spaceUsed += hashTupleSize;
		if (hashtable->spaceUsed > hashtable->spaceAllowed)
			ExecHashIncreaseNumBatches(hashtable);
	}
	else
	{


		Assert(batchno > hashtable->curbatch);
		ExecHashJoinSaveTuple(tuple,
							  hashvalue,
							  &hashtable->innerBatchFile[batchno]);
	}
}
