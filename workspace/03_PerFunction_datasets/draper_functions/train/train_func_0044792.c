Cns_opendb(dbfd)
struct Cns_dbfd *dbfd;
{
	char func[16];
	int ntries;

	strcpy (func, "Cns_opendb");
	dbfd->tr_mode = 0;
	dbfd->tr_started = 0;
	(void) mysql_init (&dbfd->mysql);
	ntries = 0;
	while (1) {
		if (mysql_real_connect (&dbfd->mysql, db_srvr, db_user, db_pwd,
		    db_name, 0, NULL, 0)) return (0);
		if (ntries++ >= MAXRETRY) break;
		sleep (RETRYI);
	}
	Cns_mysql_error (func, "CONNECT", dbfd);
	return (-1);
}
