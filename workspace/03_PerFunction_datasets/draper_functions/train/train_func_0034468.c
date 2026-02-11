amdgpu_cs_calculate_timeout(uint64_t timeout)
{
	int r;

	if (timeout != AMDGPU_TIMEOUT_INFINITE) {
		struct timespec current;
		uint64_t current_ns;
		r = clock_gettime(CLOCK_MONOTONIC, &current);
		if (r) {
			fprintf(stderr, "clock_gettime() returned error (%d)!", errno);
			return AMDGPU_TIMEOUT_INFINITE;
		}

		current_ns = ((uint64_t)current.tv_sec) * 1000000000ull;
		current_ns += current.tv_nsec;
		timeout += current_ns;
		if (timeout < current_ns)
			timeout = AMDGPU_TIMEOUT_INFINITE;
	}
	return timeout;
}
