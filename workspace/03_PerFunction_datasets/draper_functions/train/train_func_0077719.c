XLogFileOpen(uint32 log, uint32 seg)
{
	char		path[MAXPGPATH];
	int			fd;

	XLogFilePath(path, ThisTimeLineID, log, seg);

	fd = BasicOpenFile(path, O_RDWR | PG_BINARY | get_sync_bit(sync_method),
					   S_IRUSR | S_IWUSR);
	if (fd < 0)
		ereport(PANIC,
				(errcode_for_file_access(),
		   errmsg("could not open file \"%s\" (log file %u, segment %u): %m",
				  path, log, seg)));

	return fd;
}
