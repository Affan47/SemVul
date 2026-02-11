pgstat_report_recovery_conflict(int reason)
{
	PgStat_MsgRecoveryConflict msg;

	if (pgStatSock == PGINVALID_SOCKET || !pgstat_track_counts)
		return;

	pgstat_setheader(&msg.m_hdr, PGSTAT_MTYPE_RECOVERYCONFLICT);
	msg.m_databaseid = MyDatabaseId;
	msg.m_reason = reason;
	pgstat_send(&msg, sizeof(msg));
}
