ExecHashGetSkewBucket(HashJoinTable hashtable, uint32 hashvalue)
{
	int			bucket;


	if (!hashtable->skewEnabled)
		return INVALID_SKEW_BUCKET_NO;


	bucket = hashvalue & (hashtable->skewBucketLen - 1);


	while (hashtable->skewBucket[bucket] != NULL &&
		   hashtable->skewBucket[bucket]->hashvalue != hashvalue)
		bucket = (bucket + 1) & (hashtable->skewBucketLen - 1);


	if (hashtable->skewBucket[bucket] != NULL)
		return bucket;


	return INVALID_SKEW_BUCKET_NO;
}
