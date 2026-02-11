_hash_alloc_buckets(Relation rel, BlockNumber firstblock, uint32 nblocks)
{
	BlockNumber	lastblock;
	BlockNumber	endblock;
	char		zerobuf[BLCKSZ];

	lastblock = firstblock + nblocks - 1;


	if (lastblock < firstblock || lastblock == InvalidBlockNumber)
		return false;

	MemSet(zerobuf, 0, sizeof(zerobuf));

	RelationOpenSmgr(rel);


#ifndef LET_OS_MANAGE_FILESIZE
	for (endblock = firstblock | (RELSEG_SIZE - 1);
		 endblock < lastblock;
		 endblock += RELSEG_SIZE)
		smgrextend(rel->rd_smgr, endblock, zerobuf, rel->rd_istemp);
#endif

	smgrextend(rel->rd_smgr, lastblock, zerobuf, rel->rd_istemp);

	return true;
}
