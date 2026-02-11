_update_bind_type(launch_tasks_request_msg_t *req)
{
	bool set_bind = false;

	if (conf->task_plugin_param & CPU_BIND_NONE) {
		req->cpu_bind_type |= CPU_BIND_NONE;
		req->cpu_bind_type &= (~CPU_BIND_TO_SOCKETS);
		req->cpu_bind_type &= (~CPU_BIND_TO_CORES);
		req->cpu_bind_type &= (~CPU_BIND_TO_THREADS);
		req->cpu_bind_type &= (~CPU_BIND_TO_LDOMS);
		set_bind = true;
	} else if (conf->task_plugin_param & CPU_BIND_TO_SOCKETS) {
		req->cpu_bind_type &= (~CPU_BIND_NONE);
		req->cpu_bind_type |= CPU_BIND_TO_SOCKETS;
		req->cpu_bind_type &= (~CPU_BIND_TO_CORES);
		req->cpu_bind_type &= (~CPU_BIND_TO_THREADS);
		req->cpu_bind_type &= (~CPU_BIND_TO_LDOMS);
		set_bind = true;
	} else if (conf->task_plugin_param & CPU_BIND_TO_CORES) {
		req->cpu_bind_type &= (~CPU_BIND_NONE);
		req->cpu_bind_type &= (~CPU_BIND_TO_SOCKETS);
		req->cpu_bind_type |= CPU_BIND_TO_CORES;
		req->cpu_bind_type &= (~CPU_BIND_TO_THREADS);
		req->cpu_bind_type &= (~CPU_BIND_TO_LDOMS);
		set_bind = true;
	} else if (conf->task_plugin_param & CPU_BIND_TO_THREADS) {
		req->cpu_bind_type &= (~CPU_BIND_NONE);
		req->cpu_bind_type &= (~CPU_BIND_TO_SOCKETS);
		req->cpu_bind_type &= (~CPU_BIND_TO_CORES);
		req->cpu_bind_type |= CPU_BIND_TO_THREADS;
		req->cpu_bind_type &= (~CPU_BIND_TO_LDOMS);
		set_bind = true;
	} else if (conf->task_plugin_param & CPU_BIND_TO_LDOMS) {
		req->cpu_bind_type &= (~CPU_BIND_NONE);
		req->cpu_bind_type &= (~CPU_BIND_TO_SOCKETS);
		req->cpu_bind_type &= (~CPU_BIND_TO_CORES);
		req->cpu_bind_type &= (~CPU_BIND_TO_THREADS);
		req->cpu_bind_type &= CPU_BIND_TO_LDOMS;
		set_bind = true;
	}

	if (conf->task_plugin_param & CPU_BIND_VERBOSE) {
		req->cpu_bind_type |= CPU_BIND_VERBOSE;
		set_bind = true;
	}

	if (set_bind) {
		char bind_str[128];
		slurm_sprint_cpu_bind_type(bind_str, req->cpu_bind_type);
		info("task affinity : enforcing '%s' cpu bind method",
		     bind_str);
	}
}
