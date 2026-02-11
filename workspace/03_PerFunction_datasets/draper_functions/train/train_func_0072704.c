read_user_access( void )
{
	int RetCode = -1;
	static int ModTime = -2;
	static struct stat FileStat;


	if (ModTime == -2)
	{
		if (stat(userfile(),&FileStat) != 0 && errno == ENOENT) {
			if ((RetCode = create_new_file()) == 0)
				stat(userfile(),&FileStat);
			else

				return RetCode;
		}
		ModTime = FileStat.st_mtime;
	}
	else
	{
		ModTime = FileStat.st_mtime;
		stat(userfile(),&FileStat);


		if (ModTime == FileStat.st_mtime)

			return 0;
	}

	if ((RetCode = Clear_All(&NewAllEntries)) != 0)
		return RetCode;

	if ((RetCode = _read_file()) != 0)
		return RetCode;

	if ((RetCode = Clear_All(&AllEntries)) != 0)
		return RetCode;

	AllEntries = NewAllEntries;
	NewAllEntries = NULL;

	return 0;
}
