BufFileSeek(BufFile *file, int fileno, long offset, int whence)
{
	int			newFile;
	long		newOffset;

	switch (whence)
	{
		case SEEK_SET:
			if (fileno < 0)
				return EOF;
			newFile = fileno;
			newOffset = offset;
			break;
		case SEEK_CUR:


			newFile = file->curFile;
			newOffset = (file->curOffset + file->pos) + offset;
			break;
#ifdef NOT_USED
		case SEEK_END:

			break;
#endif
		default:
			elog(ERROR, "invalid whence: %d", whence);
			return EOF;
	}
	while (newOffset < 0)
	{
		if (--newFile < 0)
			return EOF;
		newOffset += MAX_PHYSICAL_FILESIZE;
	}
	if (newFile == file->curFile &&
		newOffset >= file->curOffset &&
		newOffset <= file->curOffset + file->nbytes)
	{


		file->pos = (int) (newOffset - file->curOffset);
		return 0;
	}

	if (BufFileFlush(file) != 0)
		return EOF;


	if (file->isTemp)
	{

		if (newFile == file->numFiles && newOffset == 0)
		{
			newFile--;
			newOffset = MAX_PHYSICAL_FILESIZE;
		}
		while (newOffset > MAX_PHYSICAL_FILESIZE)
		{
			if (++newFile >= file->numFiles)
				return EOF;
			newOffset -= MAX_PHYSICAL_FILESIZE;
		}
	}
	if (newFile >= file->numFiles)
		return EOF;

	file->curFile = newFile;
	file->curOffset = newOffset;
	file->pos = 0;
	file->nbytes = 0;
	return 0;
}
