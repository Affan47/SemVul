XLogFileClose(void)
{
	Assert(openLogFile >= 0);


#if defined(USE_POSIX_FADVISE) && defined(POSIX_FADV_DONTNEED)
	if (!XLogIsNeeded())
		(void) posix_fadvise(openLogFile, 0, 0, POSIX_FADV_DONTNEED);
#endif

	if (close(openLogFile))
		ereport(PANIC,
				(errcode_for_file_access(),
				 errmsg("could not close log file %u, segment %u: %m",
						openLogId, openLogSeg)));
	openLogFile = -1;
}
