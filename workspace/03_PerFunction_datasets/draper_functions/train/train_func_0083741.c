_sub_expression(char *args_spec, int task_rank, int task_offset)
{
	char tmp[BUF_SIZE];

	if (args_spec[0] == '%') {
		if (args_spec[1] == 't') {

			strcpy(tmp, &args_spec[2]);
			sprintf(args_spec, "%d%s", task_rank, tmp);
		} else if (args_spec[1] == 'o') {

			strcpy(tmp, &args_spec[2]);
			sprintf(args_spec, "%d%s", task_offset, tmp);
		}
	}
}
