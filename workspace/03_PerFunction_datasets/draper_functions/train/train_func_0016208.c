verify_socket_core_thread_count(const char *arg, int *min_sockets,
				     int *min_cores, int *min_threads,
				     cpu_bind_type_t *cpu_bind_type)
{
	bool tmp_val,ret_val;
	int i,j;
	int max_sockets, max_cores, max_threads;
	const char *cur_ptr = arg;
	char buf[3][48];
	buf[0][0] = '\0';
	buf[1][0] = '\0';
	buf[2][0] = '\0';

 	for (j=0;j<3;j++) {
		for (i=0;i<47;i++) {
			if (*cur_ptr == '\0' || *cur_ptr ==':')
				break;
			buf[j][i] = *cur_ptr++;
		}
		if (*cur_ptr == '\0')
			break;
		xassert(*cur_ptr == ':');
		buf[j][i] = '\0';
		cur_ptr++;
	}


	if (!(*cpu_bind_type & (CPU_BIND_TO_SOCKETS |
				CPU_BIND_TO_CORES |
				CPU_BIND_TO_THREADS))) {
		if (j == 0) {
			*cpu_bind_type |= CPU_BIND_TO_SOCKETS;
		} else if (j == 1) {
			*cpu_bind_type |= CPU_BIND_TO_CORES;
		} else if (j == 2) {
			*cpu_bind_type |= CPU_BIND_TO_THREADS;
		}
	}
	buf[j][i] = '\0';

	ret_val = true;
	tmp_val = get_resource_arg_range(&buf[0][0], "first arg of -B",
					 min_sockets, &max_sockets, true);
	if ((*min_sockets == 1) && (max_sockets == INT_MAX))
		*min_sockets = NO_VAL;
	ret_val = ret_val && tmp_val;

	tmp_val = get_resource_arg_range(&buf[1][0], "second arg of -B",
					 min_cores, &max_cores, true);
	if ((*min_cores == 1) && (max_cores == INT_MAX))
		*min_cores = NO_VAL;
	ret_val = ret_val && tmp_val;

	tmp_val = get_resource_arg_range(&buf[2][0], "third arg of -B",
					 min_threads, &max_threads, true);
	if ((*min_threads == 1) && (max_threads == INT_MAX))
		*min_threads = NO_VAL;
	ret_val = ret_val && tmp_val;

	return ret_val;
}
