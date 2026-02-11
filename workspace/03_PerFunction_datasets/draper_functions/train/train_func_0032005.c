mdextend(SMgrRelation reln, BlockNumber blocknum, char *buffer, bool isTemp)
{
	long		seekpos;
	int			nbytes;
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

	if ((nbytes = FileWrite(v->mdfd_vfd, buffer, BLCKSZ)) != BLCKSZ)
	{
		if (nbytes > 0)
		{
			int			save_errno = errno;


			FileTruncate(v->mdfd_vfd, seekpos);
			FileSeek(v->mdfd_vfd, seekpos, SEEK_SET);
			errno = save_errno;
		}
		return false;
	}

	if (!isTemp)
	{
		if (!register_dirty_segment(reln, v))
			return false;
	}

#ifndef LET_OS_MANAGE_FILESIZE
	Assert(_mdnblocks(v->mdfd_vfd, BLCKSZ) <= ((BlockNumber) RELSEG_SIZE));
#endif

	return true;
}
