__trace_cmd_data_output(int fd)
{
	int i;
	int nr_cpu_buffers = 0;

	for (i = 0; i < nr_cpu_ids; i++) {
		struct ring_buffer_per_cpu *cpu_buffer = &global_buffers[i];

		if (!cpu_buffer->kaddr)
			continue;

		nr_cpu_buffers++;
	}

	if (save_initial_data(fd))
		return -1;
	if (save_header_files(fd))
		return -1;
	if (save_events_files(fd))
		return -1;
	if (save_proc_kallsyms(fd))
		return -1;
	if (save_ftrace_printk(fd))
		return -1;
	if (save_ftrace_cmdlines(fd))
		return -1;
	if (save_res_data(fd, nr_cpu_buffers))
		return -1;
	if (save_record_data(fd, nr_cpu_buffers))
		return -1;

	return 0;
}
