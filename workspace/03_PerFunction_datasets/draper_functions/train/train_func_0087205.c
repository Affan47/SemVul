_do_fdump(MYSQL_ROW row, int lc)
{
	int i = 0;
	printf("\n------- Line %d -------\n", lc);
	while(jobcomp_table_fields[i].name) {
		printf("%12s: %s\n",  jobcomp_table_fields[i].name, row[i]);
		i++;
	}

	return;
}
