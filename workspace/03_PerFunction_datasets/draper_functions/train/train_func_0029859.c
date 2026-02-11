log_time( struct nvpair_database *db )
{
	time_t current = time(0);
	if(db->last_log_time!=current) {
		db->last_log_time = current;
		fprintf(db->logfile,"T %ld\n",(long)current);
	}
}
