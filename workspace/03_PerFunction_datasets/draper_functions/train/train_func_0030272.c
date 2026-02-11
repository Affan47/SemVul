pgstat_read_db_statsfile_timestamp(Oid databaseid, bool permanent,
								   TimestampTz *ts)
{
	PgStat_StatDBEntry dbentry;
	PgStat_GlobalStats myGlobalStats;
	PgStat_ArchiverStats myArchiverStats;
	FILE	   *fpin;
	int32		format_id;
	const char *statfile = permanent ? PGSTAT_STAT_PERMANENT_FILENAME : pgstat_stat_filename;


	if ((fpin = AllocateFile(statfile, PG_BINARY_R)) == NULL)
	{
		if (errno != ENOENT)
			ereport(pgStatRunningInCollector ? LOG : WARNING,
					(errcode_for_file_access(),
					 errmsg("could not open statistics file \"%s\": %m",
							statfile)));
		return false;
	}


	if (fread(&format_id, 1, sizeof(format_id), fpin) != sizeof(format_id) ||
		format_id != PGSTAT_FILE_FORMAT_ID)
	{
		ereport(pgStatRunningInCollector ? LOG : WARNING,
				(errmsg("corrupted statistics file \"%s\"", statfile)));
		FreeFile(fpin);
		return false;
	}


	if (fread(&myGlobalStats, 1, sizeof(myGlobalStats),
			  fpin) != sizeof(myGlobalStats))
	{
		ereport(pgStatRunningInCollector ? LOG : WARNING,
				(errmsg("corrupted statistics file \"%s\"", statfile)));
		FreeFile(fpin);
		return false;
	}


	if (fread(&myArchiverStats, 1, sizeof(myArchiverStats),
			  fpin) != sizeof(myArchiverStats))
	{
		ereport(pgStatRunningInCollector ? LOG : WARNING,
				(errmsg("corrupted statistics file \"%s\"", statfile)));
		FreeFile(fpin);
		return false;
	}


	*ts = myGlobalStats.stats_timestamp;


	for (;;)
	{
		switch (fgetc(fpin))
		{


			case 'D':
				if (fread(&dbentry, 1, offsetof(PgStat_StatDBEntry, tables),
						  fpin) != offsetof(PgStat_StatDBEntry, tables))
				{
					ereport(pgStatRunningInCollector ? LOG : WARNING,
							(errmsg("corrupted statistics file \"%s\"",
									statfile)));
					goto done;
				}


				if (dbentry.databaseid == databaseid)
				{
					*ts = dbentry.stats_timestamp;
					goto done;
				}

				break;

			case 'E':
				goto done;

			default:
				ereport(pgStatRunningInCollector ? LOG : WARNING,
						(errmsg("corrupted statistics file \"%s\"",
								statfile)));
				goto done;
		}
	}

done:
	FreeFile(fpin);
	return true;
}
