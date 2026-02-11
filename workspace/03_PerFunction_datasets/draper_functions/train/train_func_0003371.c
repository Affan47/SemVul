ExecHashGetBucketAndBatch(HashJoinTable hashtable,
						  uint32 hashvalue,
						  int *bucketno,
						  int *batchno)
{
	uint32		nbuckets = (uint32) hashtable->nbuckets;
	uint32		nbatch = (uint32) hashtable->nbatch;

	if (nbatch > 1)
	{
		*bucketno = hashvalue % nbuckets;

		*batchno = hash_uint32(hashvalue) & (nbatch - 1);
	}
	else
	{
		*bucketno = hashvalue % nbuckets;
		*batchno = 0;
	}
}
