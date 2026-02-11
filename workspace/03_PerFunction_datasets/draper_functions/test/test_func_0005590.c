dpm_exec_query(func, dbfd, sql_stmt, res)
char *func;
struct dpm_dbfd *dbfd;
char *sql_stmt;
MYSQL_RES **res;
{
	while(1) {
		if (dm_mysql_query (&dbfd->mysql, sql_stmt)) {
			*res = NULL;
			dpm_mysql_error (func, "mysql_query", dbfd);
			return (-1);
		}
		if ((*res = mysql_store_result (&dbfd->mysql)) == NULL) {
			if (mysql_errno (&dbfd->mysql) == ER_LOCK_WAIT_TIMEOUT) {
				dpmlogit (func, "Restarting query after lock wait timeout\n");
				continue;
			}
			dpm_mysql_error (func, "mysql_store_res", dbfd);
			return (-1);
		}
		break;
	}
	return (0);
}
