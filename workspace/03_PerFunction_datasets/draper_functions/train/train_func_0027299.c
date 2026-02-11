_hash_getbuf(Relation rel, BlockNumber blkno, int access, int flags)
{
	Buffer		buf;

	if (blkno == P_NEW)
		elog(ERROR, "hash AM does not use P_NEW");

	buf = ReadBuffer(rel, blkno);

	if (access != HASH_NOLOCK)
		LockBuffer(buf, access);


	_hash_checkpage(rel, buf, flags);

	return buf;
}
