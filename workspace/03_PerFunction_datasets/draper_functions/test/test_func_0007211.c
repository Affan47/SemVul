pg_current_xlog_insert_location(PG_FUNCTION_ARGS)
{
	XLogCtlInsert *Insert = &XLogCtl->Insert;
	XLogRecPtr	current_recptr;
	char		location[MAXFNAMELEN];

	if (RecoveryInProgress())
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("recovery is in progress"),
				 errhint("WAL control functions cannot be executed during recovery.")));


	LWLockAcquire(WALInsertLock, LW_SHARED);
	INSERT_RECPTR(current_recptr, Insert, Insert->curridx);
	LWLockRelease(WALInsertLock);

	snprintf(location, sizeof(location), "%X/%X",
			 current_recptr.xlogid, current_recptr.xrecoff);
	PG_RETURN_TEXT_P(cstring_to_text(location));
}
