cg_move_task_files(FILE *input_tasks, FILE *output_tasks)
{
	int tids;
	int ret = 0;

	while (!feof(input_tasks)) {
		ret = fscanf(input_tasks, "%d", &tids);
		if (ret == EOF || ret == 0) {
			ret = 0;
			break;
		}
		if (ret < 0)
			break;

		ret = fprintf(output_tasks, "%d", tids);
		if (ret < 0)
			break;


		ret = fflush(output_tasks);
		if (ret < 0)
			break;
	}

	if (ret < 0) {
		last_errno = errno;
		return ECGOTHER;
	}
	return 0;
}
