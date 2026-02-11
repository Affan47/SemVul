_is_array_task_id(const char *jobid)
{
	int cc;

	cc = 0;
	while (*jobid) {
		if (*jobid == '_')
			++cc;
		++jobid;
	}

	if (cc == 1)
		return true;

	return false;
}
