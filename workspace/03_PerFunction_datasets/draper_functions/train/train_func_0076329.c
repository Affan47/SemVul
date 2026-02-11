_validate_ranks(char *ranks, int ntasks, bitstr_t *task_mask)
{
	char *range = NULL, *p = NULL;
	char *ptrptr = NULL, *upper = NULL;
	int low_num, high_num;

	if (ranks[0] == '*' && ranks[1] == '\0') {
		low_num = 0;
		high_num = ntasks - 1;
		return _update_task_mask(low_num, high_num, ntasks, task_mask,
					 true);
	}

	for (range = strtok_r(ranks, ",", &ptrptr); range != NULL;
			range = strtok_r(NULL, ",", &ptrptr)) {
		p = range;
		while (*p != '\0' && isdigit (*p))
			p ++;

		if (*p == '\0') {
			low_num  = atoi(range);
			high_num = low_num;
		} else if (*p == '-') {
			upper = ++ p;
			while (isdigit (*p))
				p ++;
			if (*p != '\0') {
				error ("Invalid task range specification");
				return -1;
			}
			low_num  = atoi(range);
			high_num = atoi(upper);
		} else {
			error ("Invalid task range specification (%s)",
				range);
			return -1;
		}

		if (_update_task_mask(low_num, high_num, ntasks, task_mask,
				      false))
			return -1;
	}
	return 0;
}
