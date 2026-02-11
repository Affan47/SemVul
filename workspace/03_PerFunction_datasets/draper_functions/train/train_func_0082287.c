sql_step(sqlite3_stmt* stmt, int wait) {
	int rc;
	char looper[4] = {'|','/','-','\\'};
	int looperc = 0;
	int waited = 0;
	while (1) {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_LOCKED || rc == SQLITE_BUSY) {
			if (wait != 0) {
				fprintf(stdout,"Database is locked or busy. Waiting %is ... %1c    \r",++waited, looper[looperc]);
				fflush(stdout);
				wait--;
				looperc = looperc+1 % sizeof(looper);
				sleep(1);
			} else {
				fprintf(stderr,"Database was locked or busy while getting results. I've given up.\n");
				return rc;
			}
		} else {
			if (waited != 0) printf("\n\n");
			return rc;
		}
	}
}
