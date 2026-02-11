pgstat_report_tabstat(void)
{
	int			i;

	if (pgStatSock < 0 ||
		(!pgstat_collect_tuplelevel &&
		 !pgstat_collect_blocklevel))
	{

		RegularTabStat.tsa_used = 0;
		SharedTabStat.tsa_used = 0;
		return;
	}


	for (i = 0; i < RegularTabStat.tsa_used; i++)
	{
		PgStat_MsgTabstat *tsmsg = RegularTabStat.tsa_messages[i];
		int			n;
		int			len;

		n = tsmsg->m_nentries;
		len = offsetof(PgStat_MsgTabstat, m_entry[0]) +
			n * sizeof(PgStat_TableEntry);

		tsmsg->m_xact_commit = pgStatXactCommit;
		tsmsg->m_xact_rollback = pgStatXactRollback;
		pgStatXactCommit = 0;
		pgStatXactRollback = 0;

		pgstat_setheader(&tsmsg->m_hdr, PGSTAT_MTYPE_TABSTAT);
		tsmsg->m_databaseid = MyDatabaseId;
		pgstat_send(tsmsg, len);
	}
	RegularTabStat.tsa_used = 0;


	for (i = 0; i < SharedTabStat.tsa_used; i++)
	{
		PgStat_MsgTabstat *tsmsg = SharedTabStat.tsa_messages[i];
		int			n;
		int			len;

		n = tsmsg->m_nentries;
		len = offsetof(PgStat_MsgTabstat, m_entry[0]) +
			n * sizeof(PgStat_TableEntry);


		tsmsg->m_xact_commit = 0;
		tsmsg->m_xact_rollback = 0;

		pgstat_setheader(&tsmsg->m_hdr, PGSTAT_MTYPE_TABSTAT);
		tsmsg->m_databaseid = InvalidOid;
		pgstat_send(tsmsg, len);
	}
	SharedTabStat.tsa_used = 0;
}
