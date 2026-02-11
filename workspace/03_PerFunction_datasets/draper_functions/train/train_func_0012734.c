ExecHashTableResetMatchFlags(HashJoinTable hashtable)
{
	HashJoinTuple tuple;
	int			i;


	for (i = 0; i < hashtable->nbuckets; i++)
	{
		for (tuple = hashtable->buckets[i]; tuple != NULL; tuple = tuple->next)
			HeapTupleHeaderClearMatch(HJTUPLE_MINTUPLE(tuple));
	}


	for (i = 0; i < hashtable->nSkewBuckets; i++)
	{
		int			j = hashtable->skewBucketNums[i];
		HashSkewBucket *skewBucket = hashtable->skewBucket[j];

		for (tuple = skewBucket->tuples; tuple != NULL; tuple = tuple->next)
			HeapTupleHeaderClearMatch(HJTUPLE_MINTUPLE(tuple));
	}
}
