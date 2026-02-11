default_init(mpg123_handle *fr)
{
#if (!defined (WIN32) || defined (__CYGWIN__))
	if(fr->p.timeout > 0)
	{
		int flags;
		if(fr->rdat.r_read != NULL)
		{
			error("Timeout reading does not work with user-provided read function. Implement it yourself!");
			return -1;
		}
		flags = fcntl(fr->rdat.filept, F_GETFL);
		flags |= O_NONBLOCK;
		fcntl(fr->rdat.filept, F_SETFL, flags);
		fr->rdat.fdread = timeout_read;
		fr->rdat.timeout_sec = fr->p.timeout;
		fr->rdat.flags |= READER_NONBLOCK;
	}
	else
#endif
	fr->rdat.fdread = plain_read;

	fr->rdat.read  = fr->rdat.r_read  != NULL ? fr->rdat.r_read  : posix_read;
	fr->rdat.lseek = fr->rdat.r_lseek != NULL ? fr->rdat.r_lseek : posix_lseek;
	fr->rdat.filelen = get_fileinfo(fr);
	fr->rdat.filepos = 0;
	if(fr->rdat.filelen >= 0)
	{
		fr->rdat.flags |= READER_SEEKABLE;
		if(!strncmp((char*)fr->id3buf,"TAG",3))
		{
			fr->rdat.flags |= READER_ID3TAG;
			fr->metaflags  |= MPG123_NEW_ID3;
		}
	}

	else if(fr->p.flags & MPG123_SEEKBUFFER)
	{
#ifdef NO_FEEDER
		error("Buffered readers not supported in this build.");
		fr->err = MPG123_MISSING_FEATURE;
		return -1;
#else
		if     (fr->rd == &readers[READER_STREAM])
		{
			fr->rd = &readers[READER_BUF_STREAM];
			fr->rdat.fullread = plain_fullread;
		}
#ifndef NO_ICY
		else if(fr->rd == &readers[READER_ICY_STREAM])
		{
			fr->rd = &readers[READER_BUF_ICY_STREAM];
			fr->rdat.fullread = icy_fullread;
		}
#endif
		else
		{
			if(NOQUIET) error("mpg123 Programmer's fault: invalid reader");
			return -1;
		}
		bc_init(&fr->rdat.buffer);
		fr->rdat.filelen = 0;
		fr->rdat.flags |= READER_BUFFERED;
#endif
	}
	return 0;
}
