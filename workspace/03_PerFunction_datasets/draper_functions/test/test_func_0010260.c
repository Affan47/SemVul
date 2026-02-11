mdwrite(SMgrRelation reln, BlockNumber blocknum, char *buffer, bool isTemp)
{
	long		seekpos;
	MdfdVec    *v;

	v = _mdfd_getseg(reln, blocknum, false);

#ifndef LET_OS_MANAGE_FILESIZE
	seekpos = (long) (BLCKSZ * (blocknum % ((BlockNumber) RELSEG_SIZE)));
	Assert(seekpos < BLCKSZ * RELSEG_SIZE);
#else
	seekpos = (long) (BLCKSZ * (blocknum));
#endif

	if (FileSeek(v->mdfd_vfd, seekpos, SEEK_SET) != seekpos)
		return false;

	if (FileWrite(v->mdfd_vfd, buffer, BLCKSZ) != BLCKSZ)
		return false;

	if (!isTemp)
	{
		if (!register_dirty_segment(reln, v))
			return false;
	}

	return true;
}
