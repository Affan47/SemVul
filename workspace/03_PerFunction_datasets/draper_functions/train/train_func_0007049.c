_set_exec_names(char *ranks, char *exec_name, int ntasks)
{
	char *ptrptr = NULL, *exec_path = NULL;
	int low_num, high_num, num, i;

	exec_path = _build_path(exec_name);
	if ((ranks[0] == '*') && (ranks[1] == '\0')) {
		low_num = 0;
		high_num = ntasks - 1;
		_set_range(low_num, high_num, exec_path, true);
		return;
	}

	ptrptr = ranks;
	for (i=0; i<ntasks; i++) {
		if (!isdigit(ptrptr[0]))
			goto invalid;

		num = strtol(ptrptr, &ptrptr, 10);

		if ((ptrptr[0] == ',') || (ptrptr[0] == '\0')) {
			low_num = MAX(0, num);
			high_num = MIN((ntasks-1), num);
			_set_range(low_num, high_num, exec_path, false);
		} else if (ptrptr[0] == '-') {
			low_num = MAX(0, num);
			num = strtol(ptrptr+1, &ptrptr, 10);
			if ((ptrptr[0] != ',') && (ptrptr[0] != '\0'))
				goto invalid;
			high_num = MIN((ntasks-1), num);
			_set_range(low_num, high_num, exec_path, false);
		} else
			goto invalid;
		if (ptrptr[0] == '\0')
			break;
		ptrptr++;
	}
	return;

  invalid:
	error ("Invalid task range specification (%s) ignored.", ranks);
	return;
}
