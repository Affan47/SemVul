pgstat_recv_tabstat(PgStat_MsgTabstat *msg, int len)
{
	PgStat_StatDBEntry *dbentry;
	PgStat_StatTabEntry *tabentry;
	int			i;
	bool		found;

	dbentry = pgstat_get_db_entry(msg->m_databaseid, true);


	dbentry->n_xact_commit += (PgStat_Counter) (msg->m_xact_commit);
	dbentry->n_xact_rollback += (PgStat_Counter) (msg->m_xact_rollback);


	for (i = 0; i < msg->m_nentries; i++)
	{
		PgStat_TableEntry *tabmsg = &(msg->m_entry[i]);

		tabentry = (PgStat_StatTabEntry *) hash_search(dbentry->tables,
													(void *) &(tabmsg->t_id),
													   HASH_ENTER, &found);

		if (!found)
		{


			tabentry->numscans = tabmsg->t_counts.t_numscans;
			tabentry->tuples_returned = tabmsg->t_counts.t_tuples_returned;
			tabentry->tuples_fetched = tabmsg->t_counts.t_tuples_fetched;
			tabentry->tuples_inserted = tabmsg->t_counts.t_tuples_inserted;
			tabentry->tuples_updated = tabmsg->t_counts.t_tuples_updated;
			tabentry->tuples_deleted = tabmsg->t_counts.t_tuples_deleted;
			tabentry->tuples_hot_updated = tabmsg->t_counts.t_tuples_hot_updated;
			tabentry->n_live_tuples = tabmsg->t_counts.t_delta_live_tuples;
			tabentry->n_dead_tuples = tabmsg->t_counts.t_delta_dead_tuples;
			tabentry->changes_since_analyze = tabmsg->t_counts.t_changed_tuples;
			tabentry->blocks_fetched = tabmsg->t_counts.t_blocks_fetched;
			tabentry->blocks_hit = tabmsg->t_counts.t_blocks_hit;

			tabentry->vacuum_timestamp = 0;
			tabentry->autovac_vacuum_timestamp = 0;
			tabentry->analyze_timestamp = 0;
			tabentry->autovac_analyze_timestamp = 0;
		}
		else
		{


			tabentry->numscans += tabmsg->t_counts.t_numscans;
			tabentry->tuples_returned += tabmsg->t_counts.t_tuples_returned;
			tabentry->tuples_fetched += tabmsg->t_counts.t_tuples_fetched;
			tabentry->tuples_inserted += tabmsg->t_counts.t_tuples_inserted;
			tabentry->tuples_updated += tabmsg->t_counts.t_tuples_updated;
			tabentry->tuples_deleted += tabmsg->t_counts.t_tuples_deleted;
			tabentry->tuples_hot_updated += tabmsg->t_counts.t_tuples_hot_updated;
			tabentry->n_live_tuples += tabmsg->t_counts.t_delta_live_tuples;
			tabentry->n_dead_tuples += tabmsg->t_counts.t_delta_dead_tuples;
			tabentry->changes_since_analyze += tabmsg->t_counts.t_changed_tuples;
			tabentry->blocks_fetched += tabmsg->t_counts.t_blocks_fetched;
			tabentry->blocks_hit += tabmsg->t_counts.t_blocks_hit;
		}


		tabentry->n_live_tuples = Max(tabentry->n_live_tuples, 0);

		tabentry->n_dead_tuples = Max(tabentry->n_dead_tuples, 0);


		dbentry->n_tuples_returned += tabmsg->t_counts.t_tuples_returned;
		dbentry->n_tuples_fetched += tabmsg->t_counts.t_tuples_fetched;
		dbentry->n_tuples_inserted += tabmsg->t_counts.t_tuples_inserted;
		dbentry->n_tuples_updated += tabmsg->t_counts.t_tuples_updated;
		dbentry->n_tuples_deleted += tabmsg->t_counts.t_tuples_deleted;
		dbentry->n_blocks_fetched += tabmsg->t_counts.t_blocks_fetched;
		dbentry->n_blocks_hit += tabmsg->t_counts.t_blocks_hit;
	}
}
