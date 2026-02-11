_hash_readnext(Relation rel,
			   Buffer *bufp, Page *pagep, HashPageOpaque *opaquep)
{
	BlockNumber blkno;

	blkno = (*opaquep)->hasho_nextblkno;
	_hash_relbuf(rel, *bufp);
	*bufp = InvalidBuffer;
	if (BlockNumberIsValid(blkno))
	{
		*bufp = _hash_getbuf(rel, blkno, HASH_READ);
		_hash_checkpage(rel, *bufp, LH_OVERFLOW_PAGE);
		*pagep = BufferGetPage(*bufp);
		*opaquep = (HashPageOpaque) PageGetSpecialPointer(*pagep);
	}
}
