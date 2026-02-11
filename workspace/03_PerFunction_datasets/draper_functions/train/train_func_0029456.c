read_backup_label(XLogRecPtr *checkPointLoc, XLogRecPtr *minRecoveryLoc)
{
	XLogRecPtr	startpoint;
	XLogRecPtr	stoppoint;
	char		histfilename[MAXFNAMELEN];
	char		histfilepath[MAXPGPATH];
	char		startxlogfilename[MAXFNAMELEN];
	char		stopxlogfilename[MAXFNAMELEN];
	TimeLineID	tli;
	uint32		_logId;
	uint32		_logSeg;
	FILE	   *lfp;
	FILE	   *fp;
	char		ch;


	minRecoveryLoc->xlogid = 0;
	minRecoveryLoc->xrecoff = 0;


	lfp = AllocateFile(BACKUP_LABEL_FILE, "r");
	if (!lfp)
	{
		if (errno != ENOENT)
			ereport(FATAL,
					(errcode_for_file_access(),
					 errmsg("could not read file \"%s\": %m",
							BACKUP_LABEL_FILE)));
		return false;
	}


	if (fscanf(lfp, "START WAL LOCATION: %X/%X (file %08X%16s)%c",
			   &startpoint.xlogid, &startpoint.xrecoff, &tli,
			   startxlogfilename, &ch) != 5 || ch != '\n')
		ereport(FATAL,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("invalid data in file \"%s\"", BACKUP_LABEL_FILE)));
	if (fscanf(lfp, "CHECKPOINT LOCATION: %X/%X%c",
			   &checkPointLoc->xlogid, &checkPointLoc->xrecoff,
			   &ch) != 3 || ch != '\n')
		ereport(FATAL,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("invalid data in file \"%s\"", BACKUP_LABEL_FILE)));
	if (ferror(lfp) || FreeFile(lfp))
		ereport(FATAL,
				(errcode_for_file_access(),
				 errmsg("could not read file \"%s\": %m",
						BACKUP_LABEL_FILE)));


	XLByteToSeg(startpoint, _logId, _logSeg);
	BackupHistoryFileName(histfilename, tli, _logId, _logSeg,
						  startpoint.xrecoff % XLogSegSize);

	if (InArchiveRecovery)
		RestoreArchivedFile(histfilepath, histfilename, "RECOVERYHISTORY", 0);
	else
		BackupHistoryFilePath(histfilepath, tli, _logId, _logSeg,
							  startpoint.xrecoff % XLogSegSize);

	fp = AllocateFile(histfilepath, "r");
	if (fp)
	{


		if (fscanf(fp, "START WAL LOCATION: %X/%X (file %24s)%c",
				   &startpoint.xlogid, &startpoint.xrecoff, startxlogfilename,
				   &ch) != 4 || ch != '\n')
			ereport(FATAL,
					(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
					 errmsg("invalid data in file \"%s\"", histfilename)));
		if (fscanf(fp, "STOP WAL LOCATION: %X/%X (file %24s)%c",
				   &stoppoint.xlogid, &stoppoint.xrecoff, stopxlogfilename,
				   &ch) != 4 || ch != '\n')
			ereport(FATAL,
					(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
					 errmsg("invalid data in file \"%s\"", histfilename)));
		*minRecoveryLoc = stoppoint;
		if (ferror(fp) || FreeFile(fp))
			ereport(FATAL,
					(errcode_for_file_access(),
					 errmsg("could not read file \"%s\": %m",
							histfilepath)));
	}

	return true;
}
