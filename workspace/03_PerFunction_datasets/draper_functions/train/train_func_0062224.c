_hash_readprev(Relation rel,
			   Buffer *bufp, Page *pagep, HashPageOpaque *opaquep)
{
	BlockNumber blkno;

	blkno = (*opaquep)->hasho_prevblkno;
	_hash_relbuf(rel, *bufp);
	*bufp = InvalidBuffer;

	CHECK_FOR_INTERRUPTS();
	if (BlockNumberIsValid(blkno))
	{
		*bufp = _hash_getbuf(rel, blkno, HASH_READ,
							 LH_BUCKET_PAGE | LH_OVERFLOW_PAGE);
		*pagep = BufferGetPage(*bufp);
		*opaquep = (HashPageOpaque) PageGetSpecialPointer(*pagep);
	}
}
