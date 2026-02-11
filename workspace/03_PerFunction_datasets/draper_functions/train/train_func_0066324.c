CancelBackup(void)
{
	struct stat stat_buf;


	if (stat(BACKUP_LABEL_FILE, &stat_buf) < 0)
		return;


	unlink(BACKUP_LABEL_OLD);

	if (rename(BACKUP_LABEL_FILE, BACKUP_LABEL_OLD) != 0)
	{
		ereport(WARNING,
				(errcode_for_file_access(),
				 errmsg("online backup mode was not canceled"),
				 errdetail("File \"%s\" could not be renamed to \"%s\": %m.",
						   BACKUP_LABEL_FILE, BACKUP_LABEL_OLD)));
		return;
	}


	if (stat(TABLESPACE_MAP, &stat_buf) < 0)
	{
		ereport(LOG,
				(errmsg("online backup mode canceled"),
				 errdetail("File \"%s\" was renamed to \"%s\".",
						   BACKUP_LABEL_FILE, BACKUP_LABEL_OLD)));
		return;
	}


	unlink(TABLESPACE_MAP_OLD);

	if (rename(TABLESPACE_MAP, TABLESPACE_MAP_OLD) == 0)
	{
		ereport(LOG,
				(errmsg("online backup mode canceled"),
				 errdetail("Files \"%s\" and \"%s\" were renamed to "
						   "\"%s\" and \"%s\", respectively.",
						   BACKUP_LABEL_FILE, TABLESPACE_MAP,
						   BACKUP_LABEL_OLD, TABLESPACE_MAP_OLD)));
	}
	else
	{
		ereport(WARNING,
				(errcode_for_file_access(),
				 errmsg("online backup mode canceled"),
				 errdetail("File \"%s\" was renamed to \"%s\", but "
						   "file \"%s\" could not be renamed to \"%s\": %m.",
						   BACKUP_LABEL_FILE, BACKUP_LABEL_OLD,
						   TABLESPACE_MAP, TABLESPACE_MAP_OLD)));
	}
}
