read_loadavg(struct stats_queue *st_queue)
{
	FILE *fp;
	char line[8192];
	int load_tmp[3];

	if ((fp = fopen(LOADAVG, "r")) == NULL)
		return;


	fscanf(fp, "%d.%d %d.%d %d.%d %ld/%d %*d\n",
	       &load_tmp[0], &st_queue->load_avg_1,
	       &load_tmp[1], &st_queue->load_avg_5,
	       &load_tmp[2], &st_queue->load_avg_15,
	       &st_queue->nr_running,
	       &st_queue->nr_threads);

	fclose(fp);

	st_queue->load_avg_1  += load_tmp[0] * 100;
	st_queue->load_avg_5  += load_tmp[1] * 100;
	st_queue->load_avg_15 += load_tmp[2] * 100;

	if (st_queue->nr_running) {

		st_queue->nr_running--;
	}


	if ((fp = fopen(STAT, "r")) == NULL)
		return;

	while (fgets(line, 8192, fp) != NULL) {

		if (!strncmp(line, "procs_blocked ", 14)) {

			sscanf(line + 14, "%lu", &st_queue->procs_blocked);
			break;
		}
	}

	fclose(fp);
}
