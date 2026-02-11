pgstat_recv_vacuum(PgStat_MsgVacuum *msg, int len)
{
	PgStat_StatDBEntry *dbentry;
	PgStat_StatTabEntry *tabentry;


	dbentry = pgstat_get_db_entry(msg->m_databaseid, true);

	tabentry = pgstat_get_tab_entry(dbentry, msg->m_tableoid, true);

	if (msg->m_adopt_counts)
		tabentry->n_live_tuples = msg->m_tuples;

	tabentry->n_dead_tuples = 0;

	if (msg->m_autovacuum)
	{
		tabentry->autovac_vacuum_timestamp = msg->m_vacuumtime;
		tabentry->autovac_vacuum_count++;
	}
	else
	{
		tabentry->vacuum_timestamp = msg->m_vacuumtime;
		tabentry->vacuum_count++;
	}
}
