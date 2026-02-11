rmsummary_print(FILE *stream, struct rmsummary *s)
{
	fprintf(stream, "%-20s%20s\n",  "command:", s->command);
	fprintf(stream, "%-20s%20lf s\n", "start:", s->start >= 0 ? s->start / 1000000e0 : -1);
	fprintf(stream, "%-20s%20lf s\n", "end:",   s->end   >= 0 ? s->end   / 1000000e0 : -1);
	fprintf(stream, "%-20s%20s\n",  "exit_type:", s->exit_type);
	fprintf(stream, "%-20s%20" PRId64 "\n",  "exit_status:", s->exit_status);

	if( strcmp(s->exit_type, "signal") == 0 )
		fprintf(stream, "%-20s%20" PRId64 "\n",  "signal:", s->signal);
	else if( strcmp(s->exit_type, "limits") == 0 )
		fprintf(stream, "%-20s%s\n",  "limits_exceeded:", s->limits_exceeded);

	fprintf(stream, "%-20s%20lf s\n", "wall_time:", s->wall_time >= 0 ? s->wall_time / 1000000e0 : -1);
	fprintf(stream, "%-20s%15" PRId64 " procs\n",  "max_concurrent_processes:", s->max_concurrent_processes);
	fprintf(stream, "%-20s%20" PRId64 " procs\n",  "total_processes:", s->total_processes);
	fprintf(stream, "%-20s%20lf s\n", "cpu_time:", s->cpu_time   >= 0 ? s->cpu_time  / 1000000e0 : -1);
	fprintf(stream, "%-20s%20" PRId64 " MB\n",  "virtual_memory:", s->virtual_memory);
	fprintf(stream, "%-20s%20" PRId64 " MB\n",  "resident_memory:", s->resident_memory);
	fprintf(stream, "%-20s%20" PRId64 " MB\n",  "swap_memory:", s->swap_memory);
	fprintf(stream, "%-20s%20" PRId64 " B\n",  "bytes_read:", s->bytes_read);
	fprintf(stream, "%-20s%20" PRId64 " B\n",  "bytes_written:", s->bytes_written);
	fprintf(stream, "%-20s%20" PRId64 " files+dirs\n",  "workdir_num_files:", s->workdir_num_files);
	fprintf(stream, "%-20s%20" PRId64 " MB\n",  "workdir_footprint:",
		s->workdir_footprint >= 0 ? s->workdir_footprint : -1);
}
