read_topology(struct lscpu_desc *desc, int num)
{
	cpu_set_t *thread_siblings, *core_siblings, *book_siblings;

	if (!path_exist(_PATH_SYS_CPU "/cpu%d/topology/thread_siblings", num))
		return;

	thread_siblings = path_cpuset(_PATH_SYS_CPU
					"/cpu%d/topology/thread_siblings", num);
	core_siblings = path_cpuset(_PATH_SYS_CPU
					"/cpu%d/topology/core_siblings", num);
	book_siblings = NULL;
	if (path_exist(_PATH_SYS_CPU "/cpu%d/topology/book_siblings", num)) {
		book_siblings = path_cpuset(_PATH_SYS_CPU
					    "/cpu%d/topology/book_siblings", num);
	}

	if (!desc->coremaps) {
		int nbooks, nsockets, ncores, nthreads;
		size_t setsize = CPU_ALLOC_SIZE(maxcpus);


		nthreads = CPU_COUNT_S(setsize, thread_siblings);

		ncores = CPU_COUNT_S(setsize, core_siblings) / nthreads;


		nsockets = desc->ncpus / nthreads / ncores ?: 1;

		nbooks = desc->ncpus / nthreads / ncores / nsockets ?: 1;


		if (!desc->nthreads)
			desc->nthreads = nbooks * nsockets * ncores * nthreads;


		desc->coremaps = xcalloc(desc->ncpus, sizeof(cpu_set_t *));
		desc->socketmaps = xcalloc(desc->ncpus, sizeof(cpu_set_t *));
		if (book_siblings)
			desc->bookmaps = xcalloc(desc->ncpus, sizeof(cpu_set_t *));
	}

	add_cpuset_to_array(desc->socketmaps, &desc->nsockets, core_siblings);
	add_cpuset_to_array(desc->coremaps, &desc->ncores, thread_siblings);
	if (book_siblings)
		add_cpuset_to_array(desc->bookmaps, &desc->nbooks, book_siblings);
}
