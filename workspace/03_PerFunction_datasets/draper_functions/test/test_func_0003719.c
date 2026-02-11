ReadCheckpointRecord(XLogRecPtr RecPtr, int whichChkpt)
{
	XLogRecord *record;

	if (!XRecOffIsValid(RecPtr.xrecoff))
	{
		switch (whichChkpt)
		{
			case 1:
				ereport(LOG,
				(errmsg("invalid primary checkpoint link in control file")));
				break;
			case 2:
				ereport(LOG,
						(errmsg("invalid secondary checkpoint link in control file")));
				break;
			default:
				ereport(LOG,
				   (errmsg("invalid checkpoint link in backup_label file")));
				break;
		}
		return NULL;
	}

	record = ReadRecord(&RecPtr, LOG, true);

	if (record == NULL)
	{
		switch (whichChkpt)
		{
			case 1:
				ereport(LOG,
						(errmsg("invalid primary checkpoint record")));
				break;
			case 2:
				ereport(LOG,
						(errmsg("invalid secondary checkpoint record")));
				break;
			default:
				ereport(LOG,
						(errmsg("invalid checkpoint record")));
				break;
		}
		return NULL;
	}
	if (record->xl_rmid != RM_XLOG_ID)
	{
		switch (whichChkpt)
		{
			case 1:
				ereport(LOG,
						(errmsg("invalid resource manager ID in primary checkpoint record")));
				break;
			case 2:
				ereport(LOG,
						(errmsg("invalid resource manager ID in secondary checkpoint record")));
				break;
			default:
				ereport(LOG,
				(errmsg("invalid resource manager ID in checkpoint record")));
				break;
		}
		return NULL;
	}
	if (record->xl_info != XLOG_CHECKPOINT_SHUTDOWN &&
		record->xl_info != XLOG_CHECKPOINT_ONLINE)
	{
		switch (whichChkpt)
		{
			case 1:
				ereport(LOG,
				   (errmsg("invalid xl_info in primary checkpoint record")));
				break;
			case 2:
				ereport(LOG,
				 (errmsg("invalid xl_info in secondary checkpoint record")));
				break;
			default:
				ereport(LOG,
						(errmsg("invalid xl_info in checkpoint record")));
				break;
		}
		return NULL;
	}
	if (record->xl_len != sizeof(CheckPoint) ||
		record->xl_tot_len != SizeOfXLogRecord + sizeof(CheckPoint))
	{
		switch (whichChkpt)
		{
			case 1:
				ereport(LOG,
					(errmsg("invalid length of primary checkpoint record")));
				break;
			case 2:
				ereport(LOG,
				  (errmsg("invalid length of secondary checkpoint record")));
				break;
			default:
				ereport(LOG,
						(errmsg("invalid length of checkpoint record")));
				break;
		}
		return NULL;
	}
	return record;
}
