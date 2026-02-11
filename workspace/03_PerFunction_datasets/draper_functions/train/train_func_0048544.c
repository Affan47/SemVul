FindStreamingStart(uint32 *tli)
{
	DIR		   *dir;
	struct dirent *dirent;
	XLogSegNo	high_segno = 0;
	uint32		high_tli = 0;
	bool		high_ispartial = false;

	dir = get_destination_dir(basedir);

	while (errno = 0, (dirent = readdir(dir)) != NULL)
	{
		uint32		tli;
		XLogSegNo	segno;
		bool		ispartial;


		if (IsXLogFileName(dirent->d_name))
			ispartial = false;
		else if (IsPartialXLogFileName(dirent->d_name))
			ispartial = true;
		else
			continue;


		XLogFromFileName(dirent->d_name, &tli, &segno);


		if (!ispartial)
		{
			struct stat statbuf;
			char		fullpath[MAXPGPATH];

			snprintf(fullpath, sizeof(fullpath), "%s/%s", basedir, dirent->d_name);
			if (stat(fullpath, &statbuf) != 0)
			{
				fprintf(stderr, _("%s: could not stat file \"%s\": %s\n"),
						progname, fullpath, strerror(errno));
				disconnect_and_exit(1);
			}

			if (statbuf.st_size != XLOG_SEG_SIZE)
			{
				fprintf(stderr,
						_("%s: segment file \"%s\" has incorrect size %d, skipping\n"),
						progname, dirent->d_name, (int) statbuf.st_size);
				continue;
			}
		}


		if ((segno > high_segno) ||
			(segno == high_segno && tli > high_tli) ||
			(segno == high_segno && tli == high_tli && high_ispartial && !ispartial))
		{
			high_segno = segno;
			high_tli = tli;
			high_ispartial = ispartial;
		}
	}

	if (errno)
	{
		fprintf(stderr, _("%s: could not read directory \"%s\": %s\n"),
				progname, basedir, strerror(errno));
		disconnect_and_exit(1);
	}

	close_destination_dir(dir, basedir);

	if (high_segno > 0)
	{
		XLogRecPtr	high_ptr;


		if (!high_ispartial)
			high_segno++;

		XLogSegNoOffsetToRecPtr(high_segno, 0, high_ptr);

		*tli = high_tli;
		return high_ptr;
	}
	else
		return InvalidXLogRecPtr;
}
