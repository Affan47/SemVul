dump_semaphore_arrays(int specified, ulong specified_value, int verbose, ulong task)
{
	ulong nsproxy_p, ipc_ns_p;
	ulong ipc_ids_p;
	int (*ipc_search)(ulong, int, ulong, int (*)(ulong, int, ulong, int, int), int);
	int (*dump_sem)(ulong, int, ulong, int, int);
	char buf0[BUFSIZE];
	char buf1[BUFSIZE];
	char buf2[BUFSIZE];
	char buf3[BUFSIZE];
	char buf4[BUFSIZE];
	char buf5[BUFSIZE];

	if (specified == SPECIFIED_NOTHING) {
		fprintf(fp, "%s %s %s %s %s %s\n",
			mkstring(buf0, VADDR_PRLEN<=10?10:VADDR_PRLEN,
				LJUST, "SEM_ARRAY"),
			mkstring(buf1, 8, LJUST, "KEY"),
			mkstring(buf2, 10, LJUST, "SEMID"),
			mkstring(buf3, 5, LJUST, "UID"),
			mkstring(buf4, 5, LJUST, "PERMS"),
			mkstring(buf5, 10, LJUST, "NSEMS"));
	}

	dump_sem = dump_sem_info;

	if (VALID_MEMBER(kern_ipc_perm_id)) {
		ipc_search = ipc_search_idr;
	} else {
		ipc_search = ipc_search_array;
	}

	if (symbol_exists("sem_ids")) {
		ipc_ids_p = symbol_value("sem_ids");
	} else {
		readmem(task + OFFSET(task_struct_nsproxy), KVADDR,
			&nsproxy_p, sizeof(ulong), "task_struct.nsproxy",
			FAULT_ON_ERROR);

		if (!readmem(nsproxy_p + OFFSET(nsproxy_ipc_ns), KVADDR,
			&ipc_ns_p, sizeof(ulong), "nsproxy.ipc_ns",
			FAULT_ON_ERROR|QUIET))
			error(FATAL,
				"cannot determine ipc_namespace location!\n");

		if (MEMBER_SIZE("ipc_namespace","ids") == sizeof(ulong) * 3)
			readmem(ipc_ns_p + OFFSET(ipc_namespace_ids),
				KVADDR,	&ipc_ids_p, sizeof(ulong),
				"ipc_namespace.ids[2]",	FAULT_ON_ERROR);
		else
			ipc_ids_p = ipc_ns_p + OFFSET(ipc_namespace_ids);
	}

	return ipc_search(ipc_ids_p, specified, specified_value, dump_sem, verbose);
}
