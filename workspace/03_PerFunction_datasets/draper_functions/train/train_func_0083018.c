show_hash_info(HashState *hashstate, ExplainState *es)
{
	HashJoinTable hashtable;

	Assert(IsA(hashstate, HashState));
	hashtable = hashstate->hashtable;

	if (hashtable)
	{
		long		spacePeakKb = (hashtable->spacePeak + 1023) / 1024;

		if (es->format != EXPLAIN_FORMAT_TEXT)
		{
			ExplainPropertyLong("Hash Buckets", hashtable->nbuckets, es);
			ExplainPropertyLong("Original Hash Buckets",
								hashtable->nbuckets_original, es);
			ExplainPropertyLong("Hash Batches", hashtable->nbatch, es);
			ExplainPropertyLong("Original Hash Batches",
								hashtable->nbatch_original, es);
			ExplainPropertyLong("Peak Memory Usage", spacePeakKb, es);
		}
		else if (hashtable->nbatch_original != hashtable->nbatch ||
				 hashtable->nbuckets_original != hashtable->nbuckets)
		{
			appendStringInfoSpaces(es->str, es->indent * 2);
			appendStringInfo(es->str,
							 "Buckets: %d (originally %d)  Batches: %d (originally %d)  Memory Usage: %ldkB\n",
							 hashtable->nbuckets,
							 hashtable->nbuckets_original,
							 hashtable->nbatch,
							 hashtable->nbatch_original,
							 spacePeakKb);
		}
		else
		{
			appendStringInfoSpaces(es->str, es->indent * 2);
			appendStringInfo(es->str,
						   "Buckets: %d  Batches: %d  Memory Usage: %ldkB\n",
							 hashtable->nbuckets, hashtable->nbatch,
							 spacePeakKb);
		}
	}
}
