_hash_getbuf_with_strategy(Relation rel, BlockNumber blkno,
						   int access, int flags,
						   BufferAccessStrategy bstrategy)
{
	Buffer		buf;

	if (blkno == P_NEW)
		elog(ERROR, "hash AM does not use P_NEW");

	buf = ReadBufferExtended(rel, MAIN_FORKNUM, blkno, RBM_NORMAL, bstrategy);

	if (access != HASH_NOLOCK)
		LockBuffer(buf, access);


	_hash_checkpage(rel, buf, flags);

	return buf;
}
