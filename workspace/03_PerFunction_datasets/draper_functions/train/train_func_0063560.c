_process_running_jobs_result(char *cluster_name,
					 MYSQL_RES *result, List ret_list)
{
	MYSQL_ROW row;
	char *object;

	while ((row = mysql_fetch_row(result))) {
		if (!row[JASSOC_USER][0]) {

			error("How did we get a job running on an association "
			      "that isn't a user assocation job %s cluster "
			      "'%s' acct '%s'?", row[JASSOC_JOB],
			      cluster_name, row[JASSOC_ACCT]);
			continue;
		}
		object = xstrdup_printf(
			"JobID = %-10s C = %-10s A = %-10s U = %-9s",
			row[JASSOC_JOB], cluster_name, row[JASSOC_ACCT],
			row[JASSOC_USER]);
		if (row[JASSOC_PART][0])

			xstrfmtcat(object, " P = %s", row[JASSOC_PART]);
		list_append(ret_list, object);
	}
}
