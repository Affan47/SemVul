_ydb_close(struct ydb *ydb, int msg)
{
	struct timeval tv0, tv1;
	gettimeofday(&tv0, NULL);

	base_free(ydb->base);

	gettimeofday(&tv1, NULL);
	if (msg) {
		log_info(ydb->db, "Closing YDB database (took %lu ms)",
			 TIMEVAL_MSEC_SUBTRACT(tv1, tv0));
	}

	db_free(ydb->db);
	free(ydb);
}
